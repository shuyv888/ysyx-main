module wbu #(pc_start = 32'h80000000)
(
    input clk,
    input rst,
    input is_jalr,
    input [31:0] jalr_pc_out,
    input branch_jump,
    input [31:0] branch_pc_out,
    input is_jal,
    input [31:0] jal_pc_out,
    input inst_valid,
    input lsu_done,
    output reg [31:0] pc_reg,
    output pc_update_en
);
    assign pc_update_en = inst_valid && lsu_done;
    wire [31:0]pc_dnpc;
    assign pc_dnpc = branch_jump ? branch_pc_out :
                     is_jal      ? jal_pc_out    :
                     is_jalr     ? jalr_pc_out   :
                     (pc_reg + 4);

    always @(posedge clk) begin
        if (rst) begin
            pc_reg <= pc_start;
        end else begin
            pc_reg <= pc_update_en ? pc_dnpc : pc_reg;
        end
    end
endmodule
