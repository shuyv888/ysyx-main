// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(is_ebreak,0,0);
    VL_OUT8(illegal_instruction,0,0);
    CData/*0:0*/ top__DOT__is_add;
    CData/*0:0*/ top__DOT__is_addi;
    CData/*0:0*/ top__DOT__is_lui;
    CData/*0:0*/ top__DOT__is_lw;
    CData/*0:0*/ top__DOT__is_lbu;
    CData/*0:0*/ top__DOT__is_sw;
    CData/*0:0*/ top__DOT__is_sb;
    CData/*0:0*/ top__DOT__is_jalr;
    CData/*0:0*/ top__DOT__is_auipc;
    CData/*0:0*/ top__DOT__is_csrrw;
    CData/*0:0*/ top__DOT__inst_valid;
    CData/*0:0*/ top__DOT__wen;
    CData/*4:0*/ top__DOT__rs1_addr;
    CData/*4:0*/ top__DOT__rs2_addr;
    CData/*4:0*/ top__DOT__rd_addr;
    CData/*4:0*/ top__DOT__csr_addr;
    CData/*0:0*/ top__DOT__mem_valid;
    CData/*0:0*/ top__DOT__mem_wen;
    CData/*3:0*/ top__DOT__mem_wmask;
    CData/*0:0*/ __VstlDidInit;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactDidInit;
    CData/*0:0*/ __VactContinue;
    VL_OUT(inst,31,0);
    VL_OUT(pc,31,0);
    VL_OUT(a0,31,0);
    IData/*31:0*/ top__DOT__rs1_data;
    IData/*31:0*/ top__DOT__imm;
    IData/*31:0*/ top__DOT__pc_reg;
    IData/*31:0*/ top__DOT__mem_addr;
    IData/*31:0*/ top__DOT__ifu_rdata;
    IData/*31:0*/ top__DOT__lsu_rdata;
    IData/*31:0*/ top__DOT__u_exu__DOT__wdata_add;
    IData/*31:0*/ top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0;
    IData/*31:0*/ top__DOT__u_wbu__DOT__pc_dnpc;
    IData/*31:0*/ top__DOT__gpr__DOT__mcycle;
    IData/*31:0*/ top__DOT__gpr__DOT__mcycleh;
    IData/*31:0*/ top__DOT__gpr__DOT__mvendorid;
    IData/*31:0*/ top__DOT__gpr__DOT__marchid;
    IData/*31:0*/ __Vfunc_top__DOT__u_mem__DOT__pmem_read__1__Vfuncout;
    IData/*31:0*/ __Vfunc_top__DOT__u_mem__DOT__pmem_read__2__Vfuncout;
    IData/*31:0*/ __VactIterCount;
    QData/*63:0*/ top__DOT__gpr__DOT__mcycle_total;
    VlUnpacked<IData/*31:0*/, 32> top__DOT__dpi_gprs;
    VlUnpacked<IData/*31:0*/, 32> top__DOT__gpr__DOT__rf;
    VlUnpacked<IData/*31:0*/, 32> __Vtrigprevexpr___TOP__top__DOT__dpi_gprs__0;
    VlUnpacked<IData/*31:0*/, 32> __Vtrigprevexpr___TOP__top__DOT__dpi_gprs__1;
    VlUnpacked<CData/*0:0*/, 5> __Vm_traceActivity;
    VlTriggerVec<2> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<3> __VactTriggered;
    VlTriggerVec<3> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
