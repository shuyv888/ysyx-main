/*
WBU(WriteBack Unit): 将数据写入寄存器, 并更新PC
*/
module wbu (
  input clk,
  input rst,
  input is_jalr,
  input [31:0] jalr_pc_out,
  input inst_valid,
  input lsu_done,
  output reg [31:0] pc_reg,
  //试一试给pc_update_en给ifu
  output pc_update_en
);
  //改成assign
  // wire pc_update_en = inst_valid && lsu_done;
  assign pc_update_en = inst_valid && lsu_done;
  wire [31:0]pc_dnpc;
  assign pc_dnpc = is_jalr ? jalr_pc_out : (pc_reg + 4);


  // 更新PC逻辑
  always @(posedge clk or posedge rst) begin
    if (rst) begin
      pc_reg <= 32'h80000000;
    end else begin
      pc_reg <= pc_update_en ? pc_dnpc : pc_reg;  // 不满足则保持PC
    end
  end
endmodule
