/*
IFU(Instruction Fetch Unit):
根据SimpleBus协议实现取指功能，包含idle/wait状态机
支持1周期取指延迟，符合讲义中的时序要求
*/
module ifu (
    input               clk,        // 时钟信号（上升沿触发）
    input               rst,        // 复位信号（高有效）
    input       [31:0]  pc_reg,     // 当前PC值（来自WBU）
    input               pc_update_en,//pc是否更新
    output reg  [31:0]  ifu_raddr,  // 输出到存储器的取指地址（SimpleBus信号）
    input       [31:0]  ifu_rdata,  // 从存储器接收的指令（SimpleBus信号）
    output reg          inst_valid, // 指令有效标志（高有效，通知IDU）
    output reg  [31:0]  inst       // 输出到IDU的有效指令
);
    import "DPI-C" function int pmem_read(input int raddr);

    //reg  [31:0]  in_inst;       // 内部寄存器：暂存pmem_read的结果（用于延迟1周期）


    localparam IDLE = 1'b0;  // 空闲状态：发送取指地址
    localparam WAIT = 1'b1;  // 等待状态：等待存储器返回指令
    reg state;


//方法三，状态变更使用时序逻辑，取值使用组合逻辑
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state       <= IDLE;
        end else begin
            case (state)
                IDLE: begin
                    state       <= WAIT;
                end
                WAIT: begin
                    state       <= pc_update_en ? IDLE : WAIT;
                end
            endcase
        end
    end

    always @(*) begin
        inst = 32'b0;
        case (state)
            IDLE:begin
                ifu_raddr = pc_reg;
                inst_valid = 0;
            end 
            WAIT:begin
                inst    = ifu_rdata;
                inst_valid = 1;
            end
        endcase

    end

// // 方法二
// //只能使用这个办法，若是使用in_inst,则会导致inst滞后一个轮回(pc提前一轮回)
//     // 状态机与取指逻辑
//     always @(posedge clk or posedge rst) begin
//         if (rst) begin

//             state       <= IDLE;
//             inst        <= 32'd0;
//             //in_inst      <= 32'd0;
//             inst_valid  <= 1'b0;
//         end else begin
//             case (state)
//                 IDLE: begin
//                     inst_valid  <= 1'b0;
//                     state       <= WAIT;
//                 end
                
//                 WAIT: begin
//                     inst        <= pmem_read(pc_reg);  // 将暂存的指令输出到IDU
//                     inst_valid  <= 1'b1;
//                     state       <= IDLE;
//                 end
//             endcase
//         end
//     end

    // // 状态机与取指逻辑方法一（直接）
    // always @(posedge clk or posedge rst) begin
    //     if (rst) begin

    //         state       <= IDLE;
    //         inst        <= 32'd0;
    //         in_inst      <= 32'd0;
    //         inst_valid  <= 1'b0;
    //     end else begin
    //         case (state)
    //             IDLE: begin
    //                 in_inst      <= pmem_read(pc_reg);  // 读当前PC对应的指令，结果暂存
    //                 inst_valid  <= 1'b0;
    //                 state       <= WAIT;
    //             end
                
    //             WAIT: begin
    //                 inst        <= in_inst;  // 将暂存的指令输出到IDU
    //                 inst_valid  <= 1'b1;
    //                 state       <= IDLE;
    //             end
    //         endcase
    //     end
    // end

endmodule

