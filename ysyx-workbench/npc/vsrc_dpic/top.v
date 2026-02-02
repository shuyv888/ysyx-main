//--------------------------------------------------
// 文件：top.v
// 功能：顶层模块，连接各子模块，整合全局信号
//--------------------------------------------------
module top (
    input clk,
    input [31:0] inst,
    input rst,
    output reg [31:0] pc,
    output wire [31:0] a0,
    output is_ebreak,
    output illegal_instruction
);
    // 内部信号定义
    wire [31:0] rs1_data, rs2_data;
    wire [31:0] imm;
    wire [31:0] pc_reg;
    wire [31:0] mem_rdata;
    wire [31:0] csr_rdata;
    wire [31:0] mem_raddr;
    wire is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc, is_csrrw;
    wire [31:0] wdata;
    wire [31:0] mem_wdata;
    wire [31:0] jalr_pc_out;
    wire wen;
    wire [4:0] rs1_addr, rs2_addr, rd_addr, csr_addr;
    wire mem_valid, mem_wen;
    wire [31:0] mem_waddr;
    wire [3:0] mem_wmask;

    // EXU模块实例化
    exu u_exu (
        .rs1_data(rs1_data),
        .rs2_data(rs2_data),
        .imm(imm),
        .pc_reg(pc_reg),
        .mem_rdata(mem_rdata),
        .csr_rdata(csr_rdata),
        .mem_raddr(mem_raddr),
        .is_add(is_add),
        .is_addi(is_addi),
        .is_lui(is_lui),
        .is_lw(is_lw),
        .is_lbu(is_lbu),
        .is_sw(is_sw),
        .is_sb(is_sb),
        .is_jalr(is_jalr),
        .is_auipc(is_auipc),
        .is_csrrw(is_csrrw),
        .wdata(wdata),
        .mem_wdata(mem_wdata),
        .jalr_pc_out(jalr_pc_out)
    );

    // IDU模块实例化
    idu u_idu (
        .rst(rst),
        .inst(inst),
        .rs1_data(rs1_data),
        .wen(wen),
        .rs1_addr(rs1_addr),
        .rs2_addr(rs2_addr),
        .rd_addr(rd_addr),
        .csr_addr(csr_addr),
        .imm(imm),
        .is_add(is_add),
        .is_addi(is_addi),
        .is_lui(is_lui),
        .is_lw(is_lw),
        .is_lbu(is_lbu),
        .is_sw(is_sw),
        .is_sb(is_sb),
        .is_jalr(is_jalr),
        .is_auipc(is_auipc),
        .is_csrrw(is_csrrw),
        .mem_valid(mem_valid),
        .mem_wen(mem_wen),
        .mem_raddr(mem_raddr),
        .mem_waddr(mem_waddr),
        .mem_wmask(mem_wmask),
        .is_ebreak(is_ebreak),
        .illegal_instruction(illegal_instruction)
    );

    // LSU模块实例化
    lsu u_lsu (
        .clk(clk),
        .mem_valid(mem_valid),
        .mem_wen(mem_wen),
        .mem_raddr(mem_raddr),
        .mem_waddr(mem_waddr),
        .mem_wdata(mem_wdata),
        .mem_wmask(mem_wmask),
        .mem_rdata(mem_rdata)
    );

    // WBU模块实例化
    wbu u_wbu (
        .clk(clk),
        .rst(rst),
        .is_jalr(is_jalr),
        .jalr_pc_out(jalr_pc_out),
        .pc_reg(pc_reg)
    );

    // 寄存器文件实例化
    GPR #(
        .ADDR_WIDTH(5),
        .DATA_WIDTH(32)
    ) gpr (
        .clk(clk),
        .rst(rst),
        .wdata(wdata),
        .waddr(rd_addr),
        .wen(wen),
        .raddr1(rs1_addr),
        .raddr2(rs2_addr),
        .rdata1(rs1_data),
        .rdata2(rs2_data),
        .a0(a0),
        .csr_addr(csr_addr),
        .rs1_data(rs1_data),
        .csrrw_en(is_csrrw),
        .csr_rdata(csr_rdata)
    );
    always @(*) begin
        pc = pc_reg;
    end
endmodule

