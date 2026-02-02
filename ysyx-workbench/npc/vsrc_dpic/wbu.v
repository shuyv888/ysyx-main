/*
WBU(WriteBack Unit): 将数据写入寄存器, 并更新PC
*/
module wbu (
  input clk,
  input rst,
  input is_jalr,
  input [31:0] jalr_pc_out,
  output reg [31:0] pc_reg
);

  wire [31:0]pc_dnpc;
  assign pc_dnpc = is_jalr ? jalr_pc_out : (pc_reg + 4);
  // 更新PC逻辑
  always @(posedge clk) begin
    if (rst) begin
      pc_reg <= 32'h80000000;  //复位时PC清零
    end else begin
      pc_reg <= pc_dnpc;  //时钟沿更新PC值
    end
  end
endmodule
