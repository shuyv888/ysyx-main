module ifu (
    input               clk,
    input               rst,
    input       [31:0]  pc_reg,
    input               pc_update_en,
    input               ifu_respValid,
    output reg          ifu_reqValid,
    output      [31:0]  ifu_raddr,
    input       [31:0]  ifu_rdata,
    output reg          inst_valid,
    output reg  [31:0]  inst
);
    localparam IDLE = 1'b0;
    localparam WAIT = 1'b1;
    reg state;

    assign ifu_raddr = pc_reg;

    always @(posedge clk) begin
        if (rst) begin
            state        <= IDLE;
            ifu_reqValid <= 1'b0;
            inst_valid   <= 1'b0;
            inst         <= 32'b0;
        end else begin
            case (state)
                IDLE: begin
                    ifu_reqValid <= 1'b1;
                    state        <= WAIT;
                end
                WAIT: begin
                    ifu_reqValid <= 1'b0;

                    if (pc_update_en) begin
                        state      <= IDLE;
                        inst_valid <= 1'b0;
                    end else if (ifu_respValid) begin
                        inst       <= ifu_rdata;
                        inst_valid <= 1'b1;
                    end
                end
            endcase
        end
    end
endmodule
