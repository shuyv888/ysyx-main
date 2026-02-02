// csr



module top (
    // 全局时钟与复位
    input clk,
    input rst,
    output [31:0] inst,
    output [31:0] pc,
    output [31:0] a0,
    output is_ecall,
    output illegal_inst,
    output is_ebreak
);

    // IFU（取指单元）内部信号
    wire [31:0] ifu_raddr; // IFU内部取指地址
    wire [31:0] ifu_rdata; // IFU内部读取的指令数据
    wire ifu_reqValid; // IFU内部请求有效
    wire ifu_respValid; // IFU内部响应有效

    // LSU（加载存储单元）内部信号
    wire [31:0] lsu_addr; // LSU内部访存地址
    wire lsu_wen; // LSU内部写使能
    wire [31:0] lsu_wdata; // LSU内部写数据
    wire [3:0] lsu_wmask; // LSU内部写掩码
    wire [31:0] lsu_rdata; // LSU内部读数据
    wire lsu_reqValid; // LSU内部请求有效
    wire lsu_respValid; // LSU内部响应有效

    // EXU（执行单元）内部信号
    wire [31:0] imm; // 指令解码出的立即数
    wire [31:0] pc_reg; // 当前PC寄存器的值
    wire [31:0] rs1_data, rs2_data; // 寄存器堆读出的源寄存器数据
    wire [31:0] mem_rdata; // 内存读数据（传给EXU）
    wire [31:0] csr_rdata; // CSR读数据（传给EXU）
    wire [31:0] wdata; // 写回寄存器堆的数据
    wire [31:0] mem_addr; // 内存地址（来自EXU）
    wire [31:0] mem_wdata; // 要写入内存的数据（来自EXU）
    wire [3:0]  mem_wmask; // 内存写掩码（来自EXU）
    wire [31:0] pc_jump; // 跳转目标PC（来自EXU）
    wire jump_taken; // 是否跳转（来自EXU）
    wire [31:0] csr_wdata; // 要写入CSR的数据（来自EXU）

    // 控制信号（来自IDU指令解码）
    wire is_add, is_sub, is_sll, is_slt, is_sltu,
         is_xor, is_srl, is_sra, is_or, is_and,
         is_addi, is_slti, is_sltiu,
         is_xori, is_ori, is_andi,
         is_slli, is_srli, is_srai,
         is_lui, is_auipc,
         is_lb, is_lh, is_lw, is_lbu, is_lhu,
         is_sb, is_sh, is_sw,
         is_beq, is_bne, is_blt, is_bge, is_bltu, is_bgeu,
         is_jal, is_jalr,
         is_csrrw, is_csrrs;

    wire inst_valid; // 指令是否有效
    wire wen; // 寄存器堆写使能
    wire mem_valid; // 内存操作是否有效
    wire mem_wen; // 内存写使能
    wire lsu_done; // LSU操作是否完成
    wire pc_update_en; // PC更新使能

    // 寄存器地址信号（来自IDU）
    wire [4:0] rs1_addr, rs2_addr, rd_addr;
    wire [11:0] csr_addr;

    assign pc = pc_reg; // PC输出与内部PC寄存器同步

    // ---------------------- 子模块实例化 ----------------------
    // IFU：指令取指单元
    ifu u_ifu (
        .clk (clk),
        .rst (rst),
        .pc_reg (pc_reg),
        .pc_update_en (pc_update_en),
        .ifu_respValid (ifu_respValid),
        .ifu_reqValid (ifu_reqValid),
        .ifu_raddr (ifu_raddr),
        .ifu_rdata (ifu_rdata),
        .inst_valid (inst_valid),
        .inst (inst)
    );

    // WBU：写回与PC更新单元
    wbu #(
        .pc_start(32'h80000000) // PC起始地址参数化
    ) u_wbu (
        .clk (clk),
        .rst (rst),
        .jump_taken (jump_taken),
        .pc_jump (pc_jump),
        .inst_valid (inst_valid),
        .lsu_done (lsu_done),
        .pc_reg (pc_reg),
        .pc_update_en (pc_update_en)
    );

    // LSU：加载存储单元
    lsu u_lsu (
        .clk (clk),
        .rst (rst),
        .lsu_respValid (lsu_respValid),
        .lsu_reqValid (lsu_reqValid),
        .lsu_valid (mem_valid),
        .mem_wen (mem_wen),
        .mem_addr (mem_addr),
        .mem_wdata (mem_wdata),
        .mem_wmask (mem_wmask),
        .mem_rdata (mem_rdata),
        .lsu_done (lsu_done),
        .lsu_addr (lsu_addr),
        .lsu_wen (lsu_wen),
        .lsu_wdata (lsu_wdata),
        .lsu_wmask (lsu_wmask),
        .lsu_rdata (lsu_rdata),
        .pc_update_en (pc_update_en)
    );

    // EXU：执行单元
    exu u_exu (
        .rs1_data (rs1_data),
        .rs2_data (rs2_data),
        .imm (imm),
        .pc_reg (pc_reg),
        .mem_rdata (mem_rdata),
        .csr_rdata (csr_rdata),
        .is_add (is_add),
        .is_sub (is_sub),
        .is_sll (is_sll),
        .is_slt (is_slt),
        .is_sltu (is_sltu),
        .is_xor (is_xor),
        .is_srl (is_srl),
        .is_sra (is_sra),
        .is_or (is_or),
        .is_and (is_and),
        .is_addi (is_addi),
        .is_slti (is_slti),
        .is_sltiu (is_sltiu),
        .is_xori (is_xori),
        .is_ori (is_ori),
        .is_andi (is_andi),
        .is_slli (is_slli),
        .is_srli (is_srli),
        .is_srai (is_srai),
        .is_lui (is_lui),
        .is_auipc (is_auipc),
        .is_lb (is_lb),
        .is_lh (is_lh),
        .is_lw (is_lw),
        .is_lbu (is_lbu),
        .is_lhu (is_lhu),
        .is_sb (is_sb),
        .is_sh (is_sh),
        .is_sw (is_sw),
        .is_beq (is_beq),
        .is_bne (is_bne),
        .is_blt (is_blt),
        .is_bge (is_bge),
        .is_bltu (is_bltu),
        .is_bgeu (is_bgeu),
        .is_jal (is_jal),
        .is_jalr (is_jalr),
        .is_csrrw (is_csrrw),
        .is_csrrs (is_csrrs),
        .wdata (wdata),
        .mem_addr (mem_addr),
        .mem_wdata (mem_wdata),
        .mem_wmask (mem_wmask),
        .pc_jump (pc_jump),
        .jump_taken (jump_taken),
        .csr_wdata (csr_wdata)
    );

    // IDU：指令解码单元
    idu u_idu (
        .inst (inst),
        .inst_valid (inst_valid),
        .rs1_addr (rs1_addr),
        .rs2_addr (rs2_addr),
        .rd_addr (rd_addr),
        .imm (imm),
        .csr_addr (csr_addr),
        .wen (wen),
        .mem_valid (mem_valid),
        .mem_wen (mem_wen),
        .is_add (is_add),
        .is_sub (is_sub),
        .is_sll (is_sll),
        .is_slt (is_slt),
        .is_sltu (is_sltu),
        .is_xor (is_xor),
        .is_srl (is_srl),
        .is_sra (is_sra),
        .is_or (is_or),
        .is_and (is_and),
        .is_addi (is_addi),
        .is_slti (is_slti),
        .is_sltiu (is_sltiu),
        .is_xori (is_xori),
        .is_ori (is_ori),
        .is_andi (is_andi),
        .is_slli (is_slli),
        .is_srli (is_srli),
        .is_srai (is_srai),
        .is_lui (is_lui),
        .is_auipc (is_auipc),
        .is_lb (is_lb),
        .is_lh (is_lh),
        .is_lw (is_lw),
        .is_lbu (is_lbu),
        .is_lhu (is_lhu),
        .is_sb (is_sb),
        .is_sh (is_sh),
        .is_sw (is_sw),
        .is_beq (is_beq),
        .is_bne (is_bne),
        .is_blt (is_blt),
        .is_bge (is_bge),
        .is_bltu (is_bltu),
        .is_bgeu (is_bgeu),
        .is_jal (is_jal),
        .is_jalr (is_jalr),
        .is_csrrw (is_csrrw),
        .is_csrrs (is_csrrs),
        .is_ebreak (is_ebreak),
        .illegal_inst(illegal_inst),
        .is_ecall(is_ecall)
    );

    // GPR：通用寄存器堆
    GPR #(
        .ADDR_WIDTH(5), // 寄存器地址宽度（5位→32个寄存器）
        .DATA_WIDTH(32) // 寄存器数据宽度（32位）
    ) gpr (
        .clk (clk),
        .wdata (wdata),
        .waddr (rd_addr),
        .wen (wen),
        .pc_update_en (pc_update_en),
        .raddr1 (rs1_addr),
        .raddr2 (rs2_addr),
        .a0 (a0),
        .rdata1 (rs1_data),
        .rdata2 (rs2_data)
    );

    // CSR：控制状态寄存器
    csr u_csr (
        .clk (clk),
        .rst (rst),
        .is_csrrw (is_csrrw),
        .is_csrrs (is_csrrs),
        .csr_addr (csr_addr),
        .csr_wdata (csr_wdata),
        .csr_rdata (csr_rdata)
    );

    // mem：内存单元
    mem u_mem (
        .clk (clk),
        .ifu_reqValid (ifu_reqValid),
        .ifu_respValid (ifu_respValid),
        .ifu_raddr (ifu_raddr),
        .ifu_rdata (ifu_rdata),
        .lsu_reqValid (lsu_reqValid),
        .lsu_respValid (lsu_respValid),
        .lsu_addr (lsu_addr),
        .lsu_wen (lsu_wen),
        .lsu_wdata (lsu_wdata),
        .lsu_wmask (lsu_wmask),
        .lsu_rdata (lsu_rdata)
    );

endmodule
