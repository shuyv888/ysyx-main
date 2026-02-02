

// idu
module idu (
    input  wire [31:0] inst,           // 32位指令字
    input  wire        inst_valid,     // 该指令是否有效（非气泡、非非法等）

    // 寄存器文件读端口地址（通常直接连到 regfile）
    output reg  [4:0]  rs1_addr,      // 源寄存器1 地址
    output reg  [4:0]  rs2_addr,      // 源寄存器2 地址
    output reg  [4:0]  rd_addr,       // 目的寄存器地址

    // 立即数（各种格式已符号扩展）
    output reg  [31:0] imm,

    // CSR 相关
    output reg  [11:0] csr_addr,      // CSR 寄存器地址

    // 写回控制
    output reg         wen,           // 是否写回通用寄存器（rd）

    // 访存控制（传给 EX/MEM 阶段）
    output reg         mem_valid,     // 是否需要访存
    output reg         mem_wen,       // 访存是写（1）还是读（0））
    // ALU 操作类型（建议用 one-hot 或编码形式，根据需要定义宽度）
    // 这里用独立信号示例，便于初期调试，后期可改为 alu_op[3:0] 等
    output reg         is_add,
    output reg         is_sub,
    output reg         is_sll,
    output reg         is_slt,
    output reg         is_sltu,
    output reg         is_xor,
    output reg         is_srl,
    output reg         is_sra,
    output reg         is_or,
    output reg         is_and,

    output reg         is_addi,
    output reg         is_slti,
    output reg         is_sltiu,
    output reg         is_xori,
    output reg         is_ori,
    output reg         is_andi,
    output reg         is_slli,
    output reg         is_srli,
    output reg         is_srai,

    output reg         is_lui,
    output reg         is_auipc,

    // Load 指令类型
    output reg         is_lb,
    output reg         is_lh,
    output reg         is_lw,
    output reg         is_lbu,
    output reg         is_lhu,

    // Store 指令类型
    output reg         is_sb,
    output reg         is_sh,
    output reg         is_sw,

    // 分支指令
    output reg         is_beq,
    output reg         is_bne,
    output reg         is_blt,
    output reg         is_bge,
    output reg         is_bltu,
    output reg         is_bgeu,

    // 跳转指令
    output reg         is_jal,
    output reg         is_jalr,

    // 系统 / 特权指令
    output reg         is_ecall,
    output reg         is_ebreak,

    // CSR 指令
    output reg         is_csrrw,
    output reg         is_csrrs,
    // 非法指令指示（可选，用于异常处理）
    output reg         illegal_inst
);

    wire [6:0]  opcode = inst[6:0];
    wire [2:0]  funct3 = inst[14:12];
    wire [6:0]  funct7 = inst[31:25];
    wire [4:0]  rs1    = inst[19:15];
    wire [4:0]  rs2    = inst[24:20];
    wire [4:0]  rd     = inst[11:7];

    // 立即数模板（根据指令类型选择）
    wire [31:0] i_imm  = {{20{inst[31]}}, inst[31:20]};
    wire [31:0] s_imm  = {{20{inst[31]}}, inst[31:25], inst[11:7]};
    wire [31:0] b_imm  = {{19{inst[31]}}, inst[31], inst[7], inst[30:25], inst[11:8], 1'b0};
    wire [31:0] u_imm  = {inst[31:12], 12'b0};
    wire [31:0] j_imm  = {{11{inst[31]}}, inst[31], inst[19:12], inst[20], inst[30:21], 1'b0};

    // ──────────────────────────────────────────────
    always @(*) begin
        // 默认值（非常重要，避免锁存器）
        wen         = 1'b0;
        mem_valid   = 1'b0;
        mem_wen     = 1'b0;
        is_add      = 1'b0;
        is_sub      = 1'b0;
        is_sll      = 1'b0;
        is_slt      = 1'b0;
        is_sltu     = 1'b0;
        is_xor      = 1'b0;
        is_srl      = 1'b0;
        is_sra      = 1'b0;
        is_or       = 1'b0;
        is_and      = 1'b0;
        is_addi     = 1'b0;
        is_slti     = 1'b0;
        is_sltiu    = 1'b0;
        is_xori     = 1'b0;
        is_ori      = 1'b0;
        is_andi     = 1'b0;
        is_slli     = 1'b0;
        is_srli     = 1'b0;
        is_srai     = 1'b0;
        is_lui      = 1'b0;
        is_auipc    = 1'b0;
        is_lb       = 1'b0;
        is_lh       = 1'b0;
        is_lw       = 1'b0;
        is_lbu      = 1'b0;
        is_lhu      = 1'b0;
        is_sb       = 1'b0;
        is_sh       = 1'b0;
        is_sw       = 1'b0;
        is_beq      = 1'b0;
        is_bne      = 1'b0;
        is_blt      = 1'b0;
        is_bge      = 1'b0;
        is_bltu     = 1'b0;
        is_bgeu     = 1'b0;
        is_jal      = 1'b0;
        is_jalr     = 1'b0;
        is_ecall    = 1'b0;
        is_ebreak   = 1'b0;
        is_csrrw    = 1'b0;
        is_csrrs    = 1'b0;
        rs1_addr    = rs1;
        rs2_addr    = rs2;
        rd_addr     = rd;
        imm         = 32'b0;
        csr_addr    = 12'b0;
        // mem_addr 通常在下一级计算，这里只准备 imm
        if (inst_valid) begin
          case (opcode)
              // ──── 寄存器-寄存器运算 ────
              7'b0110011: begin           // OP
                  wen       = inst_valid;
                  rs1_addr  = rs1;
                  rs2_addr  = rs2;
                  rd_addr   = rd;
                  case (funct3)
                      3'b000: begin
                          if      (funct7 == 7'b0000000) is_add = 1;
                          else if (funct7 == 7'b0100000) is_sub = 1;
                      end
                      3'b001: if (funct7 == 7'b0000000) is_sll = 1;
                      3'b010: if (funct7 == 7'b0000000) is_slt = 1;
                      3'b011: if (funct7 == 7'b0000000) is_sltu = 1;
                      3'b100: if (funct7 == 7'b0000000) is_xor = 1;
                      3'b101: begin
                          if      (funct7 == 7'b0000000) is_srl = 1;
                          else if (funct7 == 7'b0100000) is_sra = 1;
                      end
                      3'b110: if (funct7 == 7'b0000000) is_or = 1;
                      3'b111: if (funct7 == 7'b0000000) is_and = 1;
                      default: illegal_inst = 1;
                  endcase
              end

              // ──── 立即数运算 ────
              7'b0010011: begin           // OP-IMM
                  wen       = inst_valid;
                  rs1_addr  = rs1;
                  rd_addr   = rd;
                  imm       = i_imm;

                  case (funct3)
                      3'b000: is_addi = 1;
                      3'b010: is_slti = 1;
                      3'b011: is_sltiu = 1;
                      3'b100: is_xori = 1;
                      3'b110: is_ori = 1;
                      3'b111: is_andi = 1;
                      3'b001: if  (funct7 == 7'b0000000) is_slli = 1;  // imm[11:5] must be 0
                      3'b101: begin
                          if      (funct7 == 7'b0000000) is_srli = 1;
                          else if (funct7 == 7'b0100000) is_srai = 1;
                      end
                      default: illegal_inst = 1;
                  endcase
              end

              // ──── 上位立即数 ────
              7'b0110111: begin           // LUI
                  wen       = inst_valid;
                  rd_addr   = rd;
                  imm       = u_imm;
                  is_lui    = 1;
              end
              7'b0010111: begin           // AUIPC
                  wen       = inst_valid;
                  rd_addr   = rd;
                  imm       = u_imm;
                  is_auipc  = 1;
              end

              // ──── 加载类 ────
              7'b0000011: begin           // LOAD
                  wen         = inst_valid;
                  mem_valid   = inst_valid;
                  rs1_addr    = rs1;
                  rd_addr     = rd;
                  imm         = i_imm;
                  case (funct3)
                      3'b000: is_lb  = 1;
                      3'b001: is_lh  = 1;
                      3'b010: is_lw  = 1;
                      3'b100: is_lbu = 1;
                      3'b101: is_lhu = 1;
                      default:illegal_inst = 1;
                  endcase
              end

              // ──── 存储类 ────
              7'b0100011: begin           // STORE
                  mem_valid   = inst_valid;
                  mem_wen     = inst_valid;
                  rs1_addr    = rs1;
                  rs2_addr    = rs2;
                  imm         = s_imm;
                  case (funct3)
                      3'b000: is_sb = 1;
                      3'b001: is_sh = 1;
                      3'b010: is_sw = 1;
                      default: illegal_inst = 1;
                  endcase
              end

              // ──── 分支类 ────
              7'b1100011: begin           // BRANCH
                  rs1_addr  = rs1;
                  rs2_addr  = rs2;
                  imm       = b_imm;
                  case (funct3)
                      3'b000: is_beq  = 1;
                      3'b001: is_bne  = 1;
                      3'b100: is_blt  = 1;
                      3'b101: is_bge  = 1;
                      3'b110: is_bltu = 1;
                      3'b111: is_bgeu = 1;
                      default: illegal_inst = 1;
                  endcase
              end

              // ──── 跳转类 ────
              7'b1101111: begin           // JAL
                  wen       = inst_valid;
                  rd_addr   = rd;
                  imm       = j_imm;
                  is_jal    = 1;
              end
              7'b1100111: begin           // JALR
                  if (funct3 == 3'b000) begin
                      wen       = inst_valid;
                      rs1_addr  = rs1;
                      rd_addr   = rd;
                      imm       = i_imm;
                      is_jalr   = 1;
                  end
              end
              // ──── 系统指令 / CSR ────
              7'b1110011: begin           // SYSTEM
                  rd_addr   = rd;
                  csr_addr  = inst[31:20];
                  case (funct3)
                      3'b000: begin
                          if      (inst[31:20] == 12'h000 && rs1 == 5'b0 && rd == 5'b0) is_ecall = 1;
                          else if (inst[31:20] == 12'h001 && rs1 == 5'b0 && rd == 5'b0) is_ebreak = 1;
                      end
                      3'b001: begin
                          wen       = inst_valid;
                          rs1_addr  = rs1;
                          is_csrrw  = 1;
                      end
                      3'b010: begin
                          wen       = inst_valid;
                          rs1_addr  = rs1;
                          is_csrrs  = 1;
                      end
                      default: illegal_inst = 1;
                  endcase
              end
              default:illegal_inst = 1;
          endcase
        end
    end
endmodule

