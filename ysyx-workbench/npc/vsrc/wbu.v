// wbu        已改
module wbu #(pc_start = 32'h80000000)
(
    input clk,
    input rst,
    input jump_taken,//是否更改pc
    input [31:0] pc_jump,
    input inst_valid,
    input lsu_done,
    output reg [31:0] pc_reg,
    //试一试给pc_update_en给ifu
    output pc_update_en
);
    assign pc_update_en = inst_valid && lsu_done;
    wire [31:0]pc_dnpc;
    assign pc_dnpc = jump_taken ? pc_jump : (pc_reg + 4);

    // 更新PC逻辑
    always @(posedge clk) begin
        if (rst) begin
            pc_reg <= pc_start;
        end else begin
            pc_reg <= pc_update_en ? pc_dnpc : pc_reg;  // 不满足则保持PC
        end
    end
endmodule

