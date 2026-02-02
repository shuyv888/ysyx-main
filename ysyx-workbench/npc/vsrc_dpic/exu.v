/*
EXU(EXecution Unit): 负责根据控制信号控制ALU, 对数据进行计算
*/
//--------------------------------------------------
// 文件：exu.v
//--------------------------------------------------
module exu (
  input [31:0] rs1_data,//
  input [31:0] rs2_data,//
  input [31:0] imm,//
  input [31:0] pc_reg,//
  input [31:0] mem_rdata,//
  input [31:0] csr_rdata,//
  input [31:0] mem_raddr,//
  input is_add,//
  input is_addi,//
  input is_lui,//
  input is_lw,//
  input is_lbu,//
  input is_sw,//
  input is_sb,//
  input is_jalr,//
  input is_auipc,//
  input is_csrrw,//
  output [31:0] wdata,//
  output [31:0] mem_wdata,//
  output [31:0] jalr_pc_out//
);
  wire [31:0] wdata_add, wdata_addi, wdata_lui, wdata_lw, wdata_lbu, wdata_jalr, wdata_auipc, wdata_csrrw;
  wire [31:0] mem_wdata_sw, mem_wdata_sb;

  assign wdata_add  = is_add  ? (rs1_data + rs2_data) : 32'd0;
  assign wdata_addi = is_addi ? (rs1_data + imm)      : 32'd0;
  assign wdata_lui  = is_lui  ? imm                   : 32'd0;
  assign wdata_lw   = is_lw   ? mem_rdata             : 32'd0;

  reg [7:0] lbu_byte;
  always @(*) begin
    case (mem_raddr[1:0])
      2'b00: lbu_byte = mem_rdata[7:0];
      2'b01: lbu_byte = mem_rdata[15:8];
      2'b10: lbu_byte = mem_rdata[23:16];
      2'b11: lbu_byte = mem_rdata[31:24];
      default: lbu_byte = 8'd0;
    endcase
  end
  assign wdata_lbu    = {24'b0, lbu_byte};

  assign mem_wdata_sw = rs2_data;
  assign mem_wdata_sb = rs2_data & 32'h000000FF;

  assign wdata_jalr   = pc_reg + 4;
  assign jalr_pc_out  = is_jalr  ? ((rs1_data + imm) & 32'hFFFFFFFE) :32'b0;

  assign wdata_auipc  = pc_reg + imm;

  assign wdata_csrrw  = csr_rdata;

  assign wdata =  is_add   ? wdata_add  :
                  is_addi  ? wdata_addi :
                  is_lui   ? wdata_lui  :
                  is_lw    ? wdata_lw   :
                  is_lbu   ? wdata_lbu  :
                  is_jalr  ? wdata_jalr :
                  is_auipc ? wdata_auipc:
                  is_csrrw ? wdata_csrrw:
                  32'd0;

  assign mem_wdata =  is_sw ? mem_wdata_sw :
                      is_sb ? mem_wdata_sb :
                      32'd0;
endmodule

