/*
LSU(Load-Store Unit): 
负责根据控制信号控制存储器, 从存储器中读出数据, 或将数据写入存储器
*/
module lsu (
        input               clk,        // 时钟信号（上升沿触发）
        input               rst,        // 复位信号（高有效）
        // 控制信号（来自IDU）
        input               lsu_valid,  // 访存有效标志(mem_valid)（1=需要访存）
        input               mem_wen,    // 写使能（1=store，0=load）
        input       [31:0]  mem_addr,   // 访存地址（读/写共用）
        input       [31:0]  mem_wdata,  // 待写入数据（store时有效）
        input       [3:0]   mem_wmask,  // 写掩码（每bit对应1字节，1=写入）
        // 输出信号（到EXU/WBU）
        output reg  [31:0]  mem_rdata,  // 读出的数据（load时有效）
        output reg          lsu_done,    // 访存完成标志（1=操作结束）

        output reg          lsu_reqValid, // 访存请求有效
        output reg  [31:0]  lsu_addr,    // 访存地址
        output reg          lsu_wen,     // 写使能
        output reg  [31:0]  lsu_wdata,   // 写数据
        output reg  [3:0]   lsu_wmask,   // 写掩码
        input  reg          lsu_respValid, // 访存响应有效
        input       [31:0]  lsu_rdata    // 读数据
    );
        assign lsu_wen    = mem_wen;
        assign lsu_wmask  = mem_wmask;
        assign lsu_addr   = mem_addr;
        assign lsu_wdata  = mem_wdata;



        // 状态定义（基础2状态机）
        localparam IDLE  = 1'b0;  // 空闲状态：等待访存请求
        localparam WAIT  = 1'b1;  // 等待状态：处理访存并延迟1周期

        // 内部信号
        reg         state;               // 状态寄存器
        //reg [31:0]  in_rdata;             // 读数据暂存器（延迟1周期用）
        //in_mem_wen我觉得可以优化掉
        //reg         in_mem_wen;           // 写使能暂存（同步状态用）

        always @(posedge clk or posedge rst) begin
            if (rst) begin
                state  <=IDLE;
            end else begin
                case (state)
                    IDLE: begin
                        if(lsu_valid) begin
                            if (!mem_wen) begin
                                //读操作
                                state <= WAIT;
                            end else begin
                                //写操作
                                state     <= IDLE;
                            end
                        end
                    end
                    WAIT: begin
                        if(lsu_respValid) begin
                            state     <= IDLE;
                        end
                    end
                endcase
            end
        end

        always @(*) begin
            lsu_reqValid = 0;
            case (state)
                IDLE: begin
                    lsu_addr = mem_addr;
                    lsu_reqValid = 1;
                    lsu_done = lsu_valid ? (mem_wen ? 1 : 0) : 1;
                end
                WAIT:  begin
                    if(lsu_respValid)begin
                        mem_rdata = lsu_rdata;
                    end
                    lsu_done = 1;
                end
            endcase
        end




        // //时许逻辑控制状态，
        // always @(posedge clk or posedge rst) begin
        //     if (rst) begin
        //         state  <=IDLE;
        //     end else begin
        //         in_mem_wen <= 0;
        //         lsu_reqValid <= 0;
        //         case (state)
        //             IDLE: begin
        //                 if (lsu_valid) begin
        //                     lsu_reqValid <= 1;
        //                     if (!mem_wen) begin
        //                         state     <= WAIT;
        //                         in_mem_wen   <= 1'b0;
        //                         // in_rdata  <= pmem_read(mem_addr);
        //                     end else begin
        //                         state     <= IDLE;
        //                         in_mem_wen   <= 1'b1;
        //                     end
        //                 end
        //             end
        //             WAIT: begin
        //                 if (!in_mem_wen) begin
        //                     //mem_rdata <= in_rdata;
        //                     state     <= IDLE;
        //                 end
        //             end
        //         endcase
        //     end
        // end

        
        // always @(*) begin
        //     case (state)
        //         IDLE: begin
        //             // 写操作在IDLE状态完成，读操作在IDLE状态不完成
        //             //不知道要不要直接assign
        //             lsu_addr = mem_addr;
        //             lsu_done = lsu_valid ? (mem_wen ? 1 : 0) : 1;
        //         end
        //         WAIT: begin
        //             // 读操作在WAIT状态完成
        //             mem_rdata = lsu_respValid ? lsu_rdata : 32'b0;
        //             lsu_done = 1'b1;
        //         end
        //     endcase
        // end
endmodule
