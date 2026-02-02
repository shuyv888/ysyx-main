// exu
module exu (

    input  wire [31:0] rs1_data,
    input  wire [31:0] rs2_data,
    input  wire [31:0] imm,
    input  wire [31:0] pc_reg,
    input  wire [31:0] mem_rdata,
    input  wire [31:0] csr_rdata,

    input  wire        is_add, is_sub, is_sll, is_slt, is_sltu,
    input  wire        is_xor, is_srl, is_sra, is_or,  is_and,
    input  wire        is_addi,is_slti,is_sltiu,
    input  wire        is_xori,is_ori, is_andi,
    input  wire        is_slli,is_srli,is_srai,
    input  wire        is_lui, is_auipc,
    input  wire        is_lb,  is_lh,  is_lw,  is_lbu, is_lhu,
    input  wire        is_sb,  is_sh,  is_sw,
    input  wire        is_beq, is_bne, is_blt, is_bge, is_bltu, is_bgeu,
    input  wire        is_jal, is_jalr,
    input  wire        is_csrrw, is_csrrs,

    output wire [31:0] wdata,
    output reg  [31:0] mem_addr,
    output wire [31:0] mem_wdata,
    output reg  [3:0]  mem_wmask,
    output wire [31:0] pc_jump,
    output reg         jump_taken,
    output reg  [31:0] csr_wdata
);

    // ------------------------------------------------------------------------
    // 位址生成（load / store / jalr 共用）
    // ------------------------------------------------------------------------
    always @(*) begin
        mem_addr = rs1_data + imm;
    end

    wire [31:0] wdata_add    = rs1_data + rs2_data;
    wire [31:0] wdata_sub    = rs1_data - rs2_data;
    wire [31:0] wdata_sll    = rs1_data << rs2_data[4:0];
    wire [31:0] wdata_slt    = {31'b0, $signed(rs1_data) < $signed(rs2_data)};
    wire [31:0] wdata_sltu   = {31'b0, rs1_data < rs2_data};
    wire [31:0] wdata_xor    = rs1_data ^ rs2_data;
    wire [31:0] wdata_srl    = rs1_data >> rs2_data[4:0];
    wire [31:0] wdata_sra    = $signed(rs1_data) >>> rs2_data[4:0];
    wire [31:0] wdata_or     = rs1_data | rs2_data;
    wire [31:0] wdata_and    = rs1_data & rs2_data;

    wire [31:0] wdata_addi   = rs1_data + imm;
    wire [31:0] wdata_slti   = {31'b0, $signed(rs1_data) < $signed(imm)};
    wire [31:0] wdata_sltiu  = {31'b0, rs1_data < imm};
    wire [31:0] wdata_xori   = rs1_data ^ imm;
    wire [31:0] wdata_ori    = rs1_data | imm;
    wire [31:0] wdata_andi   = rs1_data & imm;
    wire [31:0] wdata_slli   = rs1_data << imm[4:0];
    wire [31:0] wdata_srli   = rs1_data >> imm[4:0];
    wire [31:0] wdata_srai   = $signed(rs1_data) >>> imm[4:0];

    wire [31:0] wdata_lui    = imm;
    wire [31:0] wdata_auipc  = pc_reg + imm;

    
    wire [4:0] byte_offset = mem_addr[1:0] << 3;   // 0,8,16,24（对应32位数据中的4个字节起始位置）
    wire [4:0] half_offset = mem_addr[1]   << 4;   // 0,16（对应32位数据中的2个半字起始位置）

    wire [7:0]  byte_data  = mem_rdata[byte_offset +: 8];  // 取8位（1个字节），等价于 byte_offset+7 : byte_offset
    wire [15:0] half_data  = mem_rdata[half_offset +: 16];

    wire [31:0] wdata_lb   = {{24{byte_data[7]}}, byte_data};
    wire [31:0] wdata_lbu  = {24'b0, byte_data};
    wire [31:0] wdata_lh   = {{16{half_data[15]}}, half_data};
    wire [31:0] wdata_lhu  = {16'b0, half_data};

    wire [31:0] wdata_lw   = is_lw   ? mem_rdata             : 32'd0;
    wire [31:0] wdata_jal    = pc_reg + 4;
    wire [31:0] wdata_jalr   = pc_reg + 4;

    wire [31:0] wdata_csrrw  = csr_rdata;
    wire [31:0] wdata_csrrs  = csr_rdata;

    // ------------------------------------------------------------------------
    // 3. 每個 store 指令的寫記憶體資料（mem_wdata_xx）
    // ------------------------------------------------------------------------
    wire [31:0] mem_wdata_sb = (rs2_data & 32'h000000FF) << (mem_addr[1:0] * 8);
    wire [31:0] mem_wdata_sh = (rs2_data & 32'h0000FFFF) << (mem_addr[1] * 16);
    wire [31:0] mem_wdata_sw = rs2_data;

    // ------------------------------------------------------------------------
    // 4. 最終寫回 rd 的資料（選擇對應的 wdata_xx）
    // ------------------------------------------------------------------------
    assign wdata =  is_add    ? wdata_add    :
                    is_sub    ? wdata_sub    :
                    is_sll    ? wdata_sll    :
                    is_slt    ? wdata_slt    :
                    is_sltu   ? wdata_sltu   :
                    is_xor    ? wdata_xor    :
                    is_srl    ? wdata_srl    :
                    is_sra    ? wdata_sra    :
                    is_or     ? wdata_or     :
                    is_and    ? wdata_and    :
                    is_addi   ? wdata_addi   :
                    is_slti   ? wdata_slti   :
                    is_sltiu  ? wdata_sltiu  :
                    is_xori   ? wdata_xori   :
                    is_ori    ? wdata_ori    :
                    is_andi   ? wdata_andi   :
                    is_slli   ? wdata_slli   :
                    is_srli   ? wdata_srli   :
                    is_srai   ? wdata_srai   :
                    is_lui    ? wdata_lui    :
                    is_auipc  ? wdata_auipc  :
                    is_lb     ? wdata_lb     :
                    is_lh     ? wdata_lh     :
                    is_lw     ? wdata_lw     :
                    is_lbu    ? wdata_lbu    :
                    is_lhu    ? wdata_lhu    :
                    is_jal    ? wdata_jal    :
                    is_jalr   ? wdata_jalr   :
                    is_csrrw  ? wdata_csrrw  :
                    is_csrrs  ? wdata_csrrs  :
                    32'd0;

    assign mem_wdata =  is_sb ? mem_wdata_sb :
                        is_sh ? mem_wdata_sh :
                        is_sw ? mem_wdata_sw :
                        32'd0;

    // ------------------------------------------------------------------------
    // 6. 記憶體寫入 mask
    // ------------------------------------------------------------------------
    always @(*) begin
        mem_wmask = 4'b0000;
        if      (is_sw) mem_wmask = 4'b1111;
        else if (is_sh) mem_wmask = 4'b0011 << {mem_addr[1], 1'b0};
        else if (is_sb) mem_wmask = 4'b0001 << mem_addr[1:0];
    end

    // ------------------------------------------------------------------------
    // 7. CSR 寫入資料
    // ------------------------------------------------------------------------
    always @(*) begin
        csr_wdata = (is_csrrw | is_csrrs) ? rs1_data : 32'b0;
    end

    // ------------------------------------------------------------------------
    // 8. 分支是否成立
    // ------------------------------------------------------------------------
    wire        cmp_eq  = (rs1_data == rs2_data);
    wire        cmp_lt  = $signed(rs1_data)   <  $signed(rs2_data);
    wire        cmp_ltu = rs1_data            <  rs2_data;

    always @(*) begin
        jump_taken = 1'b0;
        case (1'b1)
            is_beq:  jump_taken =  cmp_eq;
            is_bne:  jump_taken = ~cmp_eq;
            is_blt:  jump_taken =  cmp_lt;
            is_bge:  jump_taken = ~cmp_lt;
            is_bltu: jump_taken =  cmp_ltu;
            is_bgeu: jump_taken = ~cmp_ltu;
            is_jal:  jump_taken = 1'b1;
            is_jalr: jump_taken = 1'b1;
            default: jump_taken = 1'b0;
        endcase
    end

    // ------------------------------------------------------------------------
    // 9. 跳轉目標位址（pc_jump）
    // ------------------------------------------------------------------------
    wire [31:0] jalr_target = (rs1_data + imm) & ~32'h1;
    assign pc_jump = is_jalr          ? jalr_target :
                    (is_jal||is_beq||is_bne||is_blt||is_bge||is_bltu||is_bgeu) ? (pc_reg + imm) :
                    32'd0;

endmodule
