
//ifu
module ifu (
    input               clk,
    input               rst,
    input       [31:0]  pc_reg,         // 来自WBU的PC
    input               pc_update_en,   // PC更新信号
    input               ifu_respValid,  // 存储器返回信号（1拍）
    output reg          ifu_reqValid,   // 取指请求信号（1拍）
    output      [31:0]  ifu_raddr,      // 取指地址
    input       [31:0]  ifu_rdata,      // 存储器返回数据
    output reg          inst_valid,     // 输出给IDU的指令有效信号
    output reg  [31:0]  inst            // 输出给IDU的指令
);

    // 状态机定义
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
                    // 发出一次取指请求（仅1周期）
                    ifu_reqValid <= 1'b1;
                    state        <= WAIT;
                end
                WAIT: begin
                    ifu_reqValid <= 1'b0;  // 请求信号自动清零

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
