/*
WBU(WriteBack Unit): 将数据写入寄存器, 并更新PC
*/
module wbu (
  input        clk,
  input        rst,
  input        is_jalr,
  input [31:0] jalr_pc_out,
  output reg [31:0] pc_reg
);

  wire [31:0] pc_dnpc = is_jalr ? jalr_pc_out : (pc_reg + 4);

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      pc_reg <= 32'h80000000;
    end else begin
      pc_reg <= pc_dnpc;
    end
  end

endmodule
