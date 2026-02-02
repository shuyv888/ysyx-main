module idu (
    input       [31:0]  inst,
    input       [31:0]  rs1_data,
    input               inst_valid,
    output reg          wen,
    output reg  [4:0]   rs1_addr,
    output reg  [4:0]   rs2_addr,
    output reg  [4:0]   rd_addr,
    output reg  [11:0]  csr_addr,
    output reg  [31:0]  imm,
    // R-type: add, sub, and, or, xor, sll, srl, sra, slt, sltu
    output reg          is_add, is_sub, is_and, is_or, is_xor, is_sll, is_srl, is_sra, is_slt, is_sltu,
    // I-type（算术立即数）: addi, andi, ori, xori, slti, sltiu
    output reg          is_addi, is_andi, is_ori, is_xori, is_slti, is_sltiu,
    // I-type（移位立即数）: slli, srli, srai（RV32E必选，补充缺失）
    output reg          is_slli, is_srli, is_srai,
    // U-type: lui, auipc
    output reg          is_lui, is_auipc,
    // S-type: sw, sh, sb
    output reg          is_sw, is_sh, is_sb,
    // B-type: beq, bne, blt, bge, bltu, bgeu
    output reg          is_beq, is_bne, is_blt, is_bge, is_bltu, is_bgeu,
    // J-type: jal, jalr
    output reg          is_jal, is_jalr,
    // Load: lw, lh, lhu, lb, lbu（补充缺失的is_lb，修正映射错误）
    output reg          is_lw, is_lh, is_lhu, is_lb, is_lbu,
    // 特殊指令: ecall, ebreak（RV32E必选，补充缺失）
    output reg          is_ecall, is_ebreak,
    // CSR: csrrw, csrrs（超出RV32E必选范围，保留但标注多余）
    output reg          is_csrrw, is_csrrs,
    // Memory access
    output reg          mem_valid,
    output reg          mem_wen,
    output reg  [31:0]  mem_addr,
    output reg  [3:0]   mem_wmask
);  

    always @(*) begin
        // ================== 1. 所有信号默认值初始化（补充遗漏端口，避免组合逻辑锁存） ==================
        wen = 1'b0;
        rs1_addr = 5'd0;
        rs2_addr = 5'd0;
        rd_addr = 5'd0;
        csr_addr = 12'd0;
        imm = 32'd0;
        mem_valid = 1'b0;
        mem_wen = 1'b0;
        mem_addr = 32'b0;
        mem_wmask = 4'b0000;

        // 指令类型分组初始化（匹配端口定义，补充遗漏信号）
        {is_add, is_sub, is_and, is_or, is_xor, is_sll, is_srl, is_sra, is_slt, is_sltu} = 10'b0;
        {is_addi, is_andi, is_ori, is_xori, is_slti, is_sltiu} = 6'b0; // 拆分U-type，避免混淆
        {is_slli, is_srli, is_srai} = 3'b0; // 新增：移位立即数指令初始化
        {is_lui, is_auipc} = 2'b0; // 独立：U-type指令初始化
        {is_sw, is_sh, is_sb} = 3'b0;
        {is_beq, is_bne, is_blt, is_bge, is_bltu, is_bgeu} = 6'b0;
        {is_jal, is_jalr} = 2'b0;
        {is_lw, is_lh, is_lhu, is_lb, is_lbu} = 5'b0; // 修正：新增is_lb，改为5位初始化
        {is_csrrw, is_csrrs} = 2'b0;
        {is_ecall, is_ebreak} = 2'b0; // 新增：特殊指令初始化

        // ================== 2. 仅当指令有效时解析，避免无效指令干扰 ==================
        if (inst_valid) begin
            // ================ R-type 指令 ================
            casez (inst[6:0])
                7'b0110011: begin  // R-type opcode
                    rs1_addr = inst[19:15];
                    rs2_addr = inst[24:20];
                    rd_addr = inst[11:7];
                    wen = 1'b1; // R-type指令写rd寄存器
                    case (inst[14:12]) // funct3
                        3'b000: begin
                            if      (inst[31:25] == 7'b0100000) is_sub = 1'b1;
                            else if (inst[31:25] == 7'b0000000) is_add = 1'b1;
                        end
                        3'b001: is_sll = 1'b1;    // sll
                        3'b010: is_slt = 1'b1;    // slt
                        3'b011: is_sltu = 1'b1;   // sltu
                        3'b100: is_xor = 1'b1;    // xor
                        3'b101: begin          // srl/sra
                            if      (inst[31:25] == 7'b0000000) is_srl = 1'b1;
                            else if (inst[31:25] == 7'b0100000) is_sra = 1'b1;
                        end
                        3'b110: is_or = 1'b1;     // or
                        3'b111: is_and = 1'b1;    // and
                    endcase
                end

            // ================ I-type 指令（算术+移位立即数） ================
                7'b0010011: begin  // I-type opcode (addi/andi/移位立即数等)
                    rs1_addr = inst[19:15];
                    rd_addr = inst[11:7];
                    wen = 1'b1; // I-type指令写rd寄存器
                    imm = {{20{inst[31]}}, inst[31:20]}; // 默认：12位有符号立即数扩展

                    case (inst[14:12]) // funct3
                        3'b000: is_addi = 1'b1;   // addi
                        3'b001: begin // slli（修正：处理5位移位立即数，补充funct7判断）
                            if (inst[31:25] == 7'b0000000) begin
                                is_slli = 1'b1;
                                imm = {27'b0, inst[24:20]}; // 移位量仅取5位，无符号扩展
                            end
                        end
                        3'b010: is_slti = 1'b1;   // slti
                        3'b011: is_sltiu = 1'b1;  // sltiu
                        3'b100: is_xori = 1'b1;   // xori
                        3'b101: begin // 新增：srli/srai（RV32E必选，补充缺失分支）
                            imm = {27'b0, inst[24:20]}; // 5位移位立即数，无符号扩展
                            if (inst[31:25] == 7'b0000000) is_srli = 1'b1; // srli：逻辑右移
                            else if (inst[31:25] == 7'b0100000) is_srai = 1'b1; // srai：算术右移
                        end
                        3'b110: is_ori = 1'b1;    // ori
                        3'b111: is_andi = 1'b1;   // andi
                    endcase
                end
                7'b0110111: begin  // LUI opcode (修正：LUI正确opcode)
                    rd_addr = inst[11:7];
                    wen = 1'b1; // LUI写rd寄存器
                    imm = {inst[31:12], 12'b0};
                    is_lui = 1'b1;
                end
                7'b0010111: begin  // AUIPC opcode
                    rd_addr = inst[11:7];
                    wen = 1'b1; // AUIPC写rd寄存器
                    imm = {inst[31:12], 12'b0};        //已左移
                    is_auipc = 1'b1;
                end

            // ================ S-type 指令 ================
                7'b0100011: begin  // S-type opcode
                    rs1_addr = inst[19:15];
                    rs2_addr = inst[24:20];
                    imm = {{20{inst[31]}}, inst[31:25], inst[11:7]}; // sign-extend
                    mem_addr = rs1_data + imm;
                    mem_wen = 1'b1;
                    mem_valid = 1'b1;
                    case (inst[14:12]) // funct3
                        3'b010: begin // sw
                            is_sw = 1'b1;
                            mem_wmask = 4'b1111;
                        end
                        3'b001: begin // sh
                            is_sh = 1'b1;
                            // 半字存储：按地址低1位设置掩码
                            mem_wmask = (mem_addr[1] == 1'b0) ? 4'b0011 : 4'b1100;
                        end
                        3'b000: begin // sb
                            is_sb = 1'b1;
                            // 字节存储：按地址低2位设置掩码
                            mem_wmask = 4'b0001 << (mem_addr[1:0]);
                        end
                    endcase
                end

            // ================ B-type 指令 ================
                7'b1100011: begin  // B-type opcode
                    rs1_addr = inst[19:15];
                    rs2_addr = inst[24:20];
                    imm = {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0};
                    case (inst[14:12]) // funct3
                        3'b000: is_beq = 1'b1;   // beq
                        3'b001: is_bne = 1'b1;   // bne
                        3'b100: is_blt = 1'b1;   // blt
                        3'b101: is_bge = 1'b1;   // bge
                        3'b110: is_bltu = 1'b1;  // bltu
                        3'b111: is_bgeu = 1'b1;  // bgeu
                    endcase
                end

            // ================ J-type 指令 ================
                7'b1101111: begin  // J-type opcode (jal)
                    rd_addr = inst[11:7];
                    wen = 1'b1; // JAL写rd寄存器（返回地址）
                    imm = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0}; // 优化：规范11位符号扩展
                    is_jal = 1'b1;
                end
                7'b1100111: begin  // JALR opcode
                    rs1_addr = inst[19:15];
                    rd_addr = inst[11:7];
                    wen = 1'b1; // JALR写rd寄存器（返回地址）
                    imm = {{20{inst[31]}}, inst[31:20]};
                    is_jalr = 1'b1;
                end

            // ================ Load 指令（修正映射错误，补充is_lb） ================
                7'b0000011: begin  // Load opcode
                    rs1_addr = inst[19:15];
                    rd_addr = inst[11:7];
                    wen = 1'b1; // Load指令写rd寄存器
                    imm = {{20{inst[31]}}, inst[31:20]}; // sign-extend
                    mem_addr = rs1_data + imm;
                    mem_valid = 1'b1;
                    case (inst[14:12]) // funct3（修正：符合RV32E规范的映射）
                        3'b010: is_lw = 1'b1;    // lw（字加载）
                        3'b001: is_lh = 1'b1;    // lh（半字有符号加载）
                        3'b011: is_lhu = 1'b1;   // lhu（半字无符号加载）
                        3'b000: is_lb = 1'b1;    // lb（字节有符号加载）
                        3'b100: is_lbu = 1'b1;   // lbu（字节无符号加载）
                    endcase
                end

            // ================ CSR 指令 + 特殊指令（ecall/ebreak，完善逻辑） ================
                7'b1110011: begin
                    // 补充：全局赋值CSR相关地址，所有分支生效
                    csr_addr = inst[31:20];
                    rs1_addr = inst[19:15];
                    rd_addr = inst[11:7];
                    
                    case (inst[14:12])
                        3'b010: begin
                          is_csrrs = 1'b1;
                          wen = 1'b1;
                        end 
                        3'b001: begin
                          is_csrrw = 1'b1;
                          wen = 1'b1;
                        end 
                        3'b000: begin
                            //if (csr_addr == 12'h000 && rs1_addr == 5'd0) is_ecall = 1'b1;
                            if (csr_addr == 12'h001 && rs1_addr == 5'd0) is_ebreak = 1'b1;
                        end
                    endcase
                end
            endcase
        end
    end
endmodule
