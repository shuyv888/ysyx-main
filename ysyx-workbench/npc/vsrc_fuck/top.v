module top (
    input         clk,
    input         rst,
    output  [31:0]  inst,
    output  [31:0]  pc,
    output  [31:0]    a0,
    output  is_ebreak
);
    assign pc=pc_reg;
    wire [31:0] ifu_raddr;
    wire [31:0] ifu_rdata;
    wire        ifu_reqValid;
    wire        ifu_respValid;

    wire [31:0] lsu_addr;
    wire        lsu_wen;
    wire [31:0] lsu_wdata;
    wire [3:0]  lsu_wmask;
    wire [31:0] lsu_rdata;
    wire        lsu_reqValid;
    wire        lsu_respValid;

    wire [31:0] imm;
    wire [31:0] pc_reg;
    wire [31:0] rs1_data, rs2_data;
    wire [31:0] mem_rdata;
    wire [31:0] csr_rdata;
    wire [31:0] wdata;
    wire [31:0] mem_wdata;
    wire [31:0] csr_wdata;
    wire [31:0] jalr_pc_out;
    wire [31:0] branch_pc_out;
    wire [31:0] jal_pc_out;
    wire [31:0] mem_addr;
    wire        branch_jump;

    wire is_add, is_sub, is_and, is_or, is_xor, is_sll, is_srl, is_sra, is_slt, is_sltu;
    wire is_addi, is_andi, is_ori, is_xori, is_slti, is_sltiu, is_lui, is_auipc;
    wire is_slli, is_srli, is_srai;
    wire is_sw, is_sh, is_sb;
    wire is_beq, is_bne, is_blt, is_bge, is_bltu, is_bgeu;
    wire is_jal, is_jalr;
    wire is_lw, is_lbu, is_lh, is_lhu;
    wire is_csrrw, is_csrrs;

   
    wire inst_valid;
    wire wen;
    wire mem_valid;
    wire mem_wen;
    wire lsu_done;
    wire pc_update_en;
    wire [3:0] mem_wmask;

    wire [4:0] rs1_addr, rs2_addr, rd_addr;
    wire [11:0] csr_addr;

    // assign io_lsu_size = (is_lbu | is_sb) ? 2'b00 :
    //                      (is_lh | is_sh) ? 2'b01 :
    //                      (is_lw | is_sw) ? 2'b10 : 2'b00;

    ifu u_ifu (
        .clk            (clk),
        .rst            (rst),
        .pc_reg         (pc_reg),
        .pc_update_en   (pc_update_en),
        .ifu_respValid  (ifu_respValid),
        .ifu_reqValid   (ifu_reqValid),
        .ifu_raddr      (ifu_raddr),
        .ifu_rdata      (ifu_rdata),
        .inst_valid     (inst_valid),
        .inst           (inst)
    );

    wbu #(
        .pc_start(32'h80000000)
    ) u_wbu (
        .clk            (clk),
        .rst            (rst),
        .is_jalr        (is_jalr),
        .jalr_pc_out    (jalr_pc_out),
        .branch_jump    (branch_jump),
        .branch_pc_out  (branch_pc_out),
        .is_jal         (is_jal),
        .jal_pc_out     (jal_pc_out),
        .inst_valid     (inst_valid),
        .lsu_done       (lsu_done),
        .pc_reg         (pc_reg),
        .pc_update_en   (pc_update_en)
    );

    lsu u_lsu (
        .clk            (clk),
        .rst            (rst),
        .lsu_respValid  (lsu_respValid),
        .lsu_reqValid   (lsu_reqValid),
        .lsu_valid      (mem_valid),
        .mem_wen        (mem_wen),
        .mem_addr       (mem_addr),
        .mem_wdata      (mem_wdata),
        .mem_wmask      (mem_wmask),
        .mem_rdata      (mem_rdata),
        .lsu_done       (lsu_done),
        .lsu_addr       (lsu_addr),
        .lsu_wen        (lsu_wen),
        .lsu_wdata      (lsu_wdata),
        .lsu_wmask      (lsu_wmask),
        .lsu_rdata      (lsu_rdata),
        .pc_update_en   (pc_update_en)
    );

    exu u_exu (
        .rs1_data       (rs1_data),
        .rs2_data       (rs2_data),
        .imm            (imm),
        .pc_reg         (pc_reg),
        .mem_rdata      (mem_rdata),
        .csr_rdata      (csr_rdata),
        .mem_addr       (mem_addr[1:0]),
        .is_add         (is_add),
        .is_addi        (is_addi),
        .is_lui         (is_lui),
        .is_lw          (is_lw),
        .is_lbu         (is_lbu),
        .is_sw          (is_sw),
        .is_sb          (is_sb),
        .is_jalr        (is_jalr),
        .is_auipc       (is_auipc),
        .is_csrrw       (is_csrrw),
        .is_csrrs       (is_csrrs),
        .is_sub         (is_sub),
        .is_and         (is_and),
        .is_andi        (is_andi),
        .is_or          (is_or),
        .is_ori         (is_ori),
        .is_xor         (is_xor),
        .is_xori        (is_xori),
        .is_sll         (is_sll),
        .is_slli        (is_slli),
        .is_srl         (is_srl),
        .is_srli        (is_srli),
        .is_sra         (is_sra),
        .is_srai        (is_srai),
        .is_slt         (is_slt),
        .is_slti        (is_slti),
        .is_sltu        (is_sltu),
        .is_sltiu       (is_sltiu),
        .is_beq         (is_beq),
        .is_bne         (is_bne),
        .is_blt         (is_blt),
        .is_bge         (is_bge),
        .is_bltu        (is_bltu),
        .is_bgeu        (is_bgeu),
        .is_jal         (is_jal),
        .is_lh          (is_lh),
        .is_lhu         (is_lhu),
        .is_sh          (is_sh),
        .wdata          (wdata),
        .mem_wdata      (mem_wdata),
        .jalr_pc_out    (jalr_pc_out),
        .branch_pc_out  (branch_pc_out),
        .jal_pc_out     (jal_pc_out),
        .branch_jump    (branch_jump),
        .csr_wdata      (csr_wdata)
    );

    idu u_idu (
        .inst               (inst),
        .inst_valid         (inst_valid),
        .rs1_data           (rs1_data),
        .wen                (wen),
        .rs1_addr           (rs1_addr),
        .rs2_addr           (rs2_addr),
        .rd_addr            (rd_addr),
        .csr_addr           (csr_addr),
        .imm                (imm),
        .is_add             (is_add),
        .is_addi            (is_addi),
        .is_lui             (is_lui),
        .is_lw              (is_lw),
        .is_lbu             (is_lbu),
        .is_sw              (is_sw),
        .is_sb              (is_sb),
        .is_jalr            (is_jalr),
        .is_auipc           (is_auipc),
        .is_csrrw           (is_csrrw),
        .is_csrrs           (is_csrrs),
        .is_sub             (is_sub),
        .is_and             (is_and),
        .is_andi            (is_andi),
        .is_or              (is_or),
        .is_ori             (is_ori),
        .is_xor             (is_xor),
        .is_xori            (is_xori),
        .is_sll             (is_sll),
        .is_slli            (is_slli),
        .is_srl             (is_srl),
        .is_srli            (is_srli),
        .is_sra             (is_sra),
        .is_srai            (is_srai),
        .is_slt             (is_slt),
        .is_slti            (is_slti),
        .is_sltu            (is_sltu),
        .is_sltiu           (is_sltiu),
        .is_beq             (is_beq),
        .is_bne             (is_bne),
        .is_blt             (is_blt),
        .is_bge             (is_bge),
        .is_bltu            (is_bltu),
        .is_bgeu            (is_bgeu),
        .is_jal             (is_jal),
        .is_lh              (is_lh),
        .is_lhu             (is_lhu),
        .is_lb              (is_lb),
        .is_sh              (is_sh),
        
        .is_ecall           (is_ecall),
        .is_ebreak          (is_ebreak),

        .mem_valid          (mem_valid),
        .mem_wen            (mem_wen),
        .mem_addr           (mem_addr),
        .mem_wmask          (mem_wmask)
    );

    GPR #(
        .ADDR_WIDTH(5),
        .DATA_WIDTH(32)
    ) gpr (
        .clk            (clk),
        .wdata          (wdata),
        .waddr          (rd_addr),
        .wen            (wen),
        .a0             (a0),
        .pc_update_en   (pc_update_en),
        .raddr1         (rs1_addr),
        .raddr2         (rs2_addr),
        .rdata1         (rs1_data),
        .rdata2         (rs2_data)
    );

    csr u_csr (
        .clk            (clk),
        .rst            (rst),
        .is_csrrw       (is_csrrw),
        .is_csrrs       (is_csrrs),
        .csr_addr       (csr_addr),
        .csr_wdata      (csr_wdata),
        .csr_rdata      (csr_rdata)
    );

    mem u_mem(
      .clk              (clk),
      .ifu_reqValid     (ifu_reqValid),
      .ifu_respValid    (ifu_respValid),
      .ifu_raddr        (ifu_raddr),
      .ifu_rdata        (ifu_rdata),
      .lsu_reqValid     (lsu_reqValid),
      .lsu_respValid    (lsu_respValid),
      .lsu_addr         (lsu_addr),
      .lsu_wen          (lsu_wen),
      .lsu_wdata        (lsu_wdata),
      .lsu_wmask        (lsu_wmask),
      .lsu_rdata        (lsu_rdata) 
    );
endmodule
