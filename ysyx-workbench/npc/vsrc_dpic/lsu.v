/*
LSU(Load-Store Unit): 
负责根据控制信号控制存储器, 从存储器中读出数据, 或将数据写入存储器
*/
module lsu (
    input               clk,        // 时钟信号（用于写操作的时序控制）
    input               mem_valid,  // 内存访问有效标志
    input               mem_wen,    // 内存写使能（1为写，0为读）
    input       [31:0]  mem_raddr,  // 内存读地址
    input       [31:0]  mem_waddr,  // 内存写地址
    input       [31:0]  mem_wdata,  // 内存写数据
    input       [3:0]   mem_wmask,  // 内存写掩码（字节使能）
    output reg  [31:0]  mem_rdata   // 内存读数据输出
);
    import "DPI-C" function int pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(
        input int mem_waddr, input int mem_wdata, input byte mem_wmask);

    always @(*) begin
        if (mem_valid) begin
            mem_rdata = pmem_read(mem_raddr);
        end else begin
            mem_rdata = 32'd0;
        end
    end

    always @(posedge clk) begin
        if (mem_valid && mem_wen) begin
            pmem_write(mem_waddr, mem_wdata, mem_wmask);
        end
    end
endmodule
