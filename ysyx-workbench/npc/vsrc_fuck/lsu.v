module lsu (
    input               clk,
    input               rst,
    input               lsu_respValid,
    output reg          lsu_reqValid,
    input               lsu_valid,
    input               mem_wen,
    input       [31:0]  mem_addr,
    input       [31:0]  mem_wdata,
    input       [3:0]   mem_wmask,
    output reg  [31:0]  mem_rdata,
    output reg          lsu_done,
    output [31:0] lsu_addr,
    output        lsu_wen,
    output [31:0] lsu_wdata,
    output [ 3:0] lsu_wmask,
    input  [31:0] lsu_rdata,
    input         pc_update_en
);
    assign lsu_wen    = mem_wen && lsu_reqValid;
    assign lsu_wmask  = mem_wmask;
    assign lsu_wdata  = mem_wdata;
    assign lsu_addr   = mem_addr;
    assign mem_rdata  = lsu_rdata;

    localparam IDLE  = 1'b0;
    localparam WAIT  = 1'b1;

    reg         state;

    always @(posedge clk) begin
        if (rst) begin
            state        <= IDLE;
            lsu_reqValid <= 0;
        end else begin
            case (state)
                IDLE: begin
                    if (lsu_valid) begin
                        state     <= WAIT;
                        lsu_reqValid <= 1;
                    end
                end
                WAIT: begin
                    if (lsu_respValid) begin
                        state <= IDLE;
                    end
                    lsu_reqValid <= 0;
                end
            endcase
        end
    end

    always @(*) begin
        case (state)
            IDLE:begin
                lsu_done = lsu_valid ? 0 : 1;
            end 
            WAIT:begin
                lsu_done = lsu_respValid ? 1 : 0;
            end
            default:lsu_done = 1;
        endcase
    end
endmodule
