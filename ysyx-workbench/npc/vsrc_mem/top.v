//--------------------------------------------------
// 文件：top.v
// 功能：顶层模块，连接各子模块，整合全局信号
//--------------------------------------------------
module top (
    input clk,
    output [31:0] inst,
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
    wire [31:0] mem_addr;
    wire is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc, is_csrrw;
    wire        inst_valid;
    wire [31:0] wdata;
    wire [31:0] mem_wdata;
    wire [31:0] jalr_pc_out;
    wire wen;
    wire [4:0] rs1_addr, rs2_addr, rd_addr, csr_addr;
    wire mem_valid, mem_wen;
    wire [3:0] mem_wmask;
    wire        lsu_done;
    wire        pc_update_en;

    wire [31:0] ifu_raddr;      // IFU读取地址
    wire [31:0] ifu_rdata;      // IFU读取数据
    
    wire [31:0] lsu_addr;       // LSU地址
    wire        lsu_wen;        // LSU写使能
    wire [31:0] lsu_wdata;      // LSU写数据
    wire [3:0]  lsu_wmask;      // LSU写掩码
    wire [31:0] lsu_rdata;      // LSU读数据


    // wire        inst_valid;           // 指令有效信号
    // wire        wen;                  // 寄存器堆写使能
    // wire        mem_valid;            // 存储器操作有效
    // wire        mem_wen;              // 存储器写使能
    // wire        lsu_done;             // LSU操作完成信号
    // wire [3:0]  mem_wmask;            // 存储器写掩码
    
    // // 地址信号
    // wire [4:0]  rs1_addr, rs2_addr;   // 源寄存器地址
    // wire [4:0]  rd_addr;              // 目的寄存器地址
    // wire [4:0]  csr_addr;             // CSR寄存器地址
    // wire [31:0] pc_reg;               // 程序计数器寄存器
    // wire [31:0] jalr_pc_out;          // JALR指令目标地址
    // wire [31:0] mem_addr;             // 存储器地址
    
    // // 数据信号
    // wire [31:0] rs1_data, rs2_data;   // 源寄存器数据
    // wire [31:0] imm;                  // 立即数
    // wire [31:0] mem_rdata;            // 存储器读数据
    // wire [31:0] csr_rdata;            // CSR寄存器读数据
    // wire [31:0] wdata;                // 写回寄存器数据
    // wire [31:0] mem_wdata;            // 存储器写数据
    
    // // 指令类型信号
    // wire is_add, is_addi, is_lui, is_lw, is_lbu, is_sw, is_sb, is_jalr, is_auipc, is_csrrw;

    assign pc = pc_reg;

    // EXU模块实例化
    ifu u_ifu(
        .clk(clk),
        .rst(rst),
        .pc_reg(pc_reg),
        .pc_update_en(pc_update_en),
        .ifu_raddr(ifu_raddr),
        .ifu_rdata(ifu_rdata),
        .inst_valid(inst_valid),
        .inst(inst)
    );
    exu u_exu (
        .rs1_data(rs1_data),
        .rs2_data(rs2_data),
        .imm(imm),
        .pc_reg(pc_reg),
        .mem_rdata(mem_rdata),
        .csr_rdata(csr_rdata),
        // .mem_raddr(mem_raddr),
        .mem_addr(mem_addr),
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
        //.clk(clk),
        .rst(rst),
        .inst(inst),
        .inst_valid(inst_valid),
        //.lsu_done(lsu_done),
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
        // .mem_raddr(mem_raddr),
        // .mem_waddr(mem_waddr),
        .mem_addr(mem_addr),
        .mem_wmask(mem_wmask),
        .is_ebreak(is_ebreak),
        .illegal_instruction(illegal_instruction)
    );

    // LSU模块实例化
    lsu u_lsu (
        .clk(clk),
        .rst(rst),
        .lsu_valid(mem_valid),
        .mem_wen(mem_wen),
        .mem_addr(mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wmask(mem_wmask),
        .mem_rdata(mem_rdata),
        .lsu_done(lsu_done),
        .lsu_addr(lsu_addr),
        .lsu_wen(lsu_wen),
        .lsu_wdata(lsu_wdata),
        .lsu_wmask(lsu_wmask),
        .lsu_rdata(lsu_rdata)
    );

    // WBU模块实例化
    wbu u_wbu (
        .clk(clk),
        .rst(rst),
        .is_jalr(is_jalr),
        .jalr_pc_out(jalr_pc_out),
        .inst_valid(inst_valid),
        .lsu_done(lsu_done),
        .pc_reg(pc_reg),
        .pc_update_en(pc_update_en)
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
        .pc_update_en(pc_update_en),
        .raddr1(rs1_addr),
        .raddr2(rs2_addr),
        .rdata1(rs1_data),
        .rdata2(rs2_data),
        .a0(a0),
        .csr_addr(csr_addr),
        .csrrw_en(is_csrrw),
        .csr_rdata(csr_rdata)
    );

    mem u_mem(
        .clk(clk),
        .ifu_raddr(ifu_raddr),
        .ifu_rdata(ifu_rdata),
        .lsu_addr(lsu_addr),
        .lsu_wen(lsu_wen),
        .lsu_wdata(lsu_wdata),
        .lsu_wmask(lsu_wmask),
        .lsu_rdata(lsu_rdata)
    );


endmodule

