module csr(
    input clk,
    input rst,

    input is_csrrw,                 // 判断指令是不是 csrrw
    input is_csrrs,
    input [11:0] csr_addr,         // SR 地址 = inst[31:20]
    input [31:0] csr_wdata,        // 要写进CSR的数据
    output reg[31:0] csr_rdata    // 从CSR寄存器读到的数据
);
    //csr寄存器
    reg [31:0] mcycle;
    reg [31:0] mcycleh;

    wire [63:0] mcycle_total;
    assign mcycle_total = {mcycleh, mcycle};

    localparam [31:0] mvendorid = 32'h79737978;
    localparam [31:0] marchid   = 32'h017eb18f;

    always @(posedge clk) begin
        if (rst) begin
            mcycle  <= 32'h00000000;
            mcycleh <= 32'h00000000;
        end else begin
            {mcycleh, mcycle} <= mcycle_total + 64'h1;            
            if (is_csrrw) begin
                case (csr_addr)
                    12'hB00: mcycle  <= csr_wdata;
                    12'hB80: mcycleh <= csr_wdata;
                    12'hF11,12'hF12: ;
                    default: ;
                endcase
            end else if(is_csrrs && csr_wdata != 32'b0) begin
                case (csr_addr)
                    12'hB00: mcycle  <= mcycle | csr_wdata;
                    12'hB80: mcycleh <= mcycleh | csr_wdata;
                    12'hF11,12'hF12: ;
                    default: ;
                endcase
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


// gpr
module GPR #(ADDR_WIDTH = 5,DATA_WIDTH = 32)
(
    input clk,
    input [DATA_WIDTH-1:0] wdata,
    input [4:0] waddr,
    input wen,
    input pc_update_en,
    input [4:0] raddr1,
    input [4:0] raddr2,
    output [DATA_WIDTH-1:0] a0,
    output [DATA_WIDTH-1:0] rdata1,
    output [DATA_WIDTH-1:0] rdata2
);
    //当pc更新时才写寄存器
    wire reg_wen;
    assign reg_wen = wen && pc_update_en;

    //普通寄存器
    reg [DATA_WIDTH-1:0] rf [(1<<ADDR_WIDTH)-1:0];

    always @(posedge clk) begin
        if (reg_wen && (waddr != 0)) rf[waddr[ADDR_WIDTH-1:0]] <= wdata;
    end

    assign rdata1 = (raddr1 == 5'd0) ? {DATA_WIDTH{1'b0}} : rf[raddr1[ADDR_WIDTH-1:0]];
    assign rdata2 = (raddr2 == 5'd0) ? {DATA_WIDTH{1'b0}} : rf[raddr2[ADDR_WIDTH-1:0]];
    assign a0 = rf[10];
endmodule


module mem (
    input               clk,        // 时钟信号（写操作使用）
    // IFU取指接口
    input               ifu_reqValid,
    output reg          ifu_respValid,
    input       [31:0]  ifu_raddr,   // 取指地址（来自IFU的pc_reg）
    output      [31:0]  ifu_rdata,   // 输出指令（给IFU的inst）
    // LSU访存接口
    input               lsu_reqValid,
    output reg          lsu_respValid,
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

    always @(posedge clk) begin
        ifu_rdata <= ifu_reqValid ? pmem_read(ifu_raddr) : 32'b0;
        ifu_respValid <= ifu_reqValid;
    end

    always @(posedge clk) begin
        lsu_rdata <= (lsu_reqValid && !lsu_wen) ? pmem_read(lsu_addr) : 32'b0;
        if (lsu_reqValid && lsu_wen) begin
            pmem_write(lsu_addr, lsu_wdata, lsu_wmask);
        end
        lsu_respValid <= lsu_reqValid;
    end
endmodule

