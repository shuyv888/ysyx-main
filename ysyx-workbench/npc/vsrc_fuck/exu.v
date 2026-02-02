module exu (
    input [31:0] rs1_data,
    input [31:0] rs2_data,
    input [31:0] imm,
    input [31:0] pc_reg,
    input [31:0] mem_rdata,
    input [31:0] csr_rdata,
    input [1:0]  mem_addr,//已经取了addr的最后两位
    input        is_add , is_addi , is_lui , is_auipc, is_lw   , is_lbu  ,
    input        is_sw  , is_sb   , is_jalr, is_csrrw, is_csrrs,
    input        is_sub , is_and  , is_andi, is_or   , is_ori  ,
    input        is_xor , is_xori , is_sll , is_slli , is_srl  ,
    input        is_srli, is_sra  , is_srai, is_slt  , is_slti ,
    input        is_sltu, is_sltiu, is_beq , is_bne  , is_blt  ,
    input        is_bge , is_bltu , is_bgeu, is_jal  , is_lh   ,
    input        is_lhu , is_sh,
    output [31:0] wdata,
    output [31:0] mem_wdata,
    output [31:0] jalr_pc_out,
    output [31:0] branch_pc_out,
    output [31:0] jal_pc_out,
    output reg    branch_jump,
    output [31:0] csr_wdata
);
    wire [31:0] wdata_add, wdata_addi, wdata_lui, wdata_auipc, wdata_lw, wdata_lbu, wdata_jalr;
    wire [31:0] wdata_sub, wdata_and, wdata_andi, wdata_or, wdata_ori, wdata_xor, wdata_xori;
    wire [31:0] wdata_sll, wdata_slli, wdata_srl, wdata_srli, wdata_sra, wdata_srai;
    wire [31:0] wdata_slt, wdata_slti, wdata_sltu, wdata_sltiu, wdata_jal, wdata_lh, wdata_lhu;
    wire [31:0] mem_wdata_sw, mem_wdata_sb, mem_wdata_sh;

    assign wdata_add   = is_add    ? (rs1_data + rs2_data) : 32'd0;
    assign wdata_addi  = is_addi   ? (rs1_data + imm)      : 32'd0;
    assign wdata_lui   = is_lui    ? imm                   : 32'd0;
    assign wdata_auipc = is_auipc  ? pc_reg + imm          : 32'd0; //imm已左移，其他可能不同，有问题注意看
    assign wdata_lw    = is_lw     ? mem_rdata             : 32'd0;

    reg [7:0] lbu_byte;
    always @(*) begin
        case (mem_addr)
            2'b00: lbu_byte = mem_rdata[7:0];
            2'b01: lbu_byte = mem_rdata[15:8];
            2'b10: lbu_byte = mem_rdata[23:16];
            2'b11: lbu_byte = mem_rdata[31:24];
            default: lbu_byte = 8'd0;
        endcase
    end
    assign wdata_lbu    = is_lbu ? {24'b0, lbu_byte} : 32'd0;

    reg [15:0] lh_half, lhu_half;
    always @(*) begin
        case (mem_addr[1])
            1'b0: begin lh_half = mem_rdata[15:0]; lhu_half = mem_rdata[15:0]; end
            1'b1: begin lh_half = mem_rdata[31:16]; lhu_half = mem_rdata[31:16]; end
            default: begin lh_half = 16'd0; lhu_half = 16'd0; end
        endcase
    end
    assign wdata_lh     = is_lh  ? {{16{lh_half[15]}}, lh_half} : 32'd0;
    assign wdata_lhu    = is_lhu ? {16'b0, lhu_half} : 32'd0;

    assign wdata_sub    = is_sub  ? (rs1_data - rs2_data) : 32'd0;
    assign wdata_and    = is_and  ? (rs1_data & rs2_data) : 32'd0;
    assign wdata_andi   = is_andi ? (rs1_data & imm)      : 32'd0;
    assign wdata_or     = is_or   ? (rs1_data | rs2_data) : 32'd0;
    assign wdata_ori    = is_ori  ? (rs1_data | imm)      : 32'd0;
    assign wdata_xor    = is_xor  ? (rs1_data ^ rs2_data) : 32'd0;
    assign wdata_xori   = is_xori ? (rs1_data ^ imm)      : 32'd0;

    wire [4:0] shamt_r = rs2_data[4:0];
    wire [4:0] shamt_i = imm[4:0];
    assign wdata_sll    = is_sll  ? (rs1_data << shamt_r) : 32'd0;
    assign wdata_slli   = is_slli ? (rs1_data << shamt_i) : 32'd0;
    assign wdata_srl    = is_srl  ? (rs1_data >> shamt_r) : 32'd0;
    assign wdata_srli   = is_srli ? (rs1_data >> shamt_i) : 32'd0;
    assign wdata_sra    = is_sra  ? ($signed(rs1_data) >>> shamt_r) : 32'd0;
    assign wdata_srai   = is_srai ? ($signed(rs1_data) >>> shamt_i) : 32'd0;

    assign wdata_slt    = is_slt  ? ($signed(rs1_data) < $signed(rs2_data) ? 32'd1 : 32'd0) : 32'd0;
    assign wdata_slti   = is_slti ? ($signed(rs1_data) < $signed(imm)      ? 32'd1 : 32'd0) : 32'd0;
    assign wdata_sltu   = is_sltu ? (rs1_data < rs2_data ? 32'd1 : 32'd0) : 32'd0;
    assign wdata_sltiu  = is_sltiu? (rs1_data < imm      ? 32'd1 : 32'd0) : 32'd0;

    assign mem_wdata_sw = rs2_data;
    assign mem_wdata_sb = (rs2_data & 32'h000000FF) << (mem_addr * 8);
    assign mem_wdata_sh = (rs2_data & 32'h0000FFFF) << (mem_addr[1] * 16);

    assign wdata_jalr   = pc_reg + 4;
    assign jalr_pc_out  = is_jalr ? ((rs1_data + imm) & 32'hFFFFFFFE) : 32'b0;

    assign wdata_jal    = pc_reg + 4;
    assign jal_pc_out   = is_jal ? (pc_reg + imm) : 32'b0;

    assign branch_pc_out = pc_reg + imm;
    always @(*) begin
        branch_jump = 1'b0;
        if (is_beq)    branch_jump = (rs1_data == rs2_data);
        else if (is_bne) branch_jump = (rs1_data != rs2_data);
        else if (is_blt) branch_jump = ($signed(rs1_data) < $signed(rs2_data));
        else if (is_bge) branch_jump = ($signed(rs1_data) >= $signed(rs2_data));
        else if (is_bltu)branch_jump = (rs1_data < rs2_data);
        else if (is_bgeu)branch_jump = (rs1_data >= rs2_data);
    end

    assign csr_wdata  = (is_csrrw | is_csrrs) ? rs1_data : 32'b0;

    assign wdata =  is_add   ? wdata_add  :
                    is_addi  ? wdata_addi :
                    is_lui   ? wdata_lui  :
                    is_auipc ? wdata_auipc:
                    is_lw    ? wdata_lw   :
                    is_lbu   ? wdata_lbu  :
                    is_jalr  ? wdata_jalr :
                    (is_csrrw | is_csrrs) ? csr_rdata  :
                    is_sub   ? wdata_sub  :
                    is_and   ? wdata_and  :
                    is_andi  ? wdata_andi :
                    is_or    ? wdata_or   :
                    is_ori   ? wdata_ori  :
                    is_xor   ? wdata_xor  :
                    is_xori  ? wdata_xori :
                    is_sll   ? wdata_sll  :
                    is_slli  ? wdata_slli :
                    is_srl   ? wdata_srl  :
                    is_srli  ? wdata_srli :
                    is_sra   ? wdata_sra  :
                    is_srai  ? wdata_srai :
                    is_slt   ? wdata_slt  :
                    is_slti  ? wdata_slti :
                    is_sltu  ? wdata_sltu :
                    is_sltiu ? wdata_sltiu:
                    is_jal   ? wdata_jal  :
                    is_lh    ? wdata_lh   :
                    is_lhu   ? wdata_lhu  :
                    32'd0;

    assign mem_wdata =  is_sw ? mem_wdata_sw :
                        is_sb ? mem_wdata_sb :
                        is_sh ? mem_wdata_sh :
                        32'd0;
endmodule
