//--------------------------------------------------
// 文件：RegisterFile.v
//--------------------------------------------------
module GPR #(ADDR_WIDTH = 5,DATA_WIDTH = 32)
(
    input clk,
    input rst,
    input [DATA_WIDTH-1:0] wdata,
    input [ADDR_WIDTH-1:0] waddr,
    input wen,
    input pc_update_en,
    input [ADDR_WIDTH-1:0] raddr1,
    input [ADDR_WIDTH-1:0] raddr2,
    output [DATA_WIDTH-1:0] rdata1,
    output [DATA_WIDTH-1:0] rdata2,
    output [DATA_WIDTH-1:0] a0,

    //csr使用
    input [ADDR_WIDTH-1:0] csr_addr,
    input csrrw_en,
    output reg [DATA_WIDTH-1:0] csr_rdata
);
    //当pc更新时才写寄存器
    wire reg_wen;
    assign reg_wen = wen && pc_update_en;


    //普通寄存器
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    always @(posedge clk) begin
        if (reg_wen && (waddr != 0)) rf[waddr] <= wdata;
    end

    assign rdata1 = (raddr1 == 0) ? 0 : rf[raddr1];
    assign rdata2 = (raddr2 == 0) ? 0 : rf[raddr2];
    assign a0 = rf[10];



    //csr寄存器
    reg [31:0] mcycle;
    reg [31:0] mcycleh;
    reg [31:0] mvendorid;
    reg [31:0] marchid;

    wire [63:0] mcycle_total;
    assign mcycle_total = {mcycleh, mcycle};

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            mcycle  <= 32'h00000000;
            mcycleh <= 32'h00000000;
            mvendorid <= 32'h79737978;
            marchid   <= 32'h017eb18f;
        end else begin
            if (csrrw_en && (csr_addr == 12'hb00)) begin
                mcycle <= wdata;
            end else if (csrrw_en && (csr_addr == 12'hb80)) begin
                mcycleh <= wdata;
            end else begin
                {mcycleh, mcycle} <= mcycle_total + 64'h1;
            end
        end
    end

    always @(*) begin
        case (csr_addr)
            12'hb00: csr_rdata = mcycle;
            12'hb80: csr_rdata = mcycleh;
            12'hf11: csr_rdata = mvendorid;
            12'hf12: csr_rdata = marchid;
            default: csr_rdata = 32'h00000000;
        endcase
    end
endmodule


module mem (
    input               clk,        // 时钟信号（写操作使用）
    // IFU取指接口
    input       [31:0]  ifu_raddr,   // 取指地址（来自IFU的pc_reg）
    output reg  [31:0]  ifu_rdata,   // 输出指令（给IFU的inst）
    // LSU访存接口
    input       [31:0]  lsu_addr,   // 访存地址（来自LSU的mem_addr）
    input               lsu_wen,    // 写使能（1=写，0=读）
    input       [31:0]  lsu_wdata,  // 写数据（来自LSU的mem_wdata）
    input       [3:0]   lsu_wmask,  // 写掩码（来自LSU的mem_wmask）
    output reg  [31:0]  lsu_rdata   // 读数据（给LSU的mem_rdata）
);
    // DPI-C存储器接口（复用原有pmem函数）
    import "DPI-C" function int pmem_read(input int raddr);
    import "DPI-C" function void pmem_write(
        input int waddr, input int wdata, input byte wmask);

    // ------------------------------
    // 1. IFU取指：组合逻辑，无延迟
    // ------------------------------
    always @(*) begin
        // 直接读取当前地址对应的指令，输出给IFU
        ifu_rdata = pmem_read(ifu_raddr);
    end

    // ------------------------------
    // 2. LSU读操作：组合逻辑，无延迟
    // ------------------------------
    always @(*) begin
        if (!lsu_wen) begin  // 读操作（lw/lbu）
            lsu_rdata = pmem_read(lsu_addr);
        end else begin
            lsu_rdata = 32'd0;  // 写操作时读数据无效
        end
    end

    // ------------------------------
    // 3. LSU写操作：时序逻辑，时钟边沿执行
    // ------------------------------
    always @(posedge clk) begin
        if (lsu_wen) begin  // 写操作（sw/sb）
            pmem_write(lsu_addr, lsu_wdata, lsu_wmask);
        end
    end

endmodule
