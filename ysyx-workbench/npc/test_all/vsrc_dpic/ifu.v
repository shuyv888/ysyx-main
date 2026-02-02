
module ifu (
    input [31:0] pc_reg,
    output [31:0] inst
);
    import "DPI-C" function int pmem_read(input int raddr);

    assign inst       = pmem_read(pc_reg);

endmodule

