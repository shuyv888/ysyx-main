//--------------------------------------------------
// 文件：RegisterFile.v
//--------------------------------------------------
module GPR #(ADDR_WIDTH = 5,DATA_WIDTH = 32)
(
    input clk,//
    input rst,////
    input [DATA_WIDTH-1:0] wdata,//
    input [ADDR_WIDTH-1:0] waddr,//
    input wen,//
    input [ADDR_WIDTH-1:0] raddr1,//
    input [ADDR_WIDTH-1:0] raddr2,//
    output [DATA_WIDTH-1:0] rdata1,//
    output [DATA_WIDTH-1:0] rdata2,//
    output [DATA_WIDTH-1:0] a0,//
    input [ADDR_WIDTH-1:0] csr_addr,////
    input [DATA_WIDTH-1:0] rs1_data,////
    input csrrw_en,////
    output reg [DATA_WIDTH-1:0] csr_rdata////
);

    //普通寄存器
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    always @(posedge clk) begin
        if (wen && (waddr != 0)) rf[waddr] <= wdata;
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
                mcycle <= rs1_data;
            end else if (csrrw_en && (csr_addr == 12'hb80)) begin
                mcycleh <= rs1_data;
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
