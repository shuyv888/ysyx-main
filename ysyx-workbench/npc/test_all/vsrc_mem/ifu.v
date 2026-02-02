/*
IFU(Instruction Fetch Unit):
根据SimpleBus协议实现取指功能，包含idle/wait状态机
支持1周期取指延迟，符合讲义中的时序要求
*/
module ifu (
    input [31:0] pc_reg,
    output [31:0] ifu_raddr,
    input  [31:0] ifu_rdata,
    output [31:0] inst
);

    assign ifu_raddr  = pc_reg;
    assign inst       = ifu_rdata;

endmodule

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


