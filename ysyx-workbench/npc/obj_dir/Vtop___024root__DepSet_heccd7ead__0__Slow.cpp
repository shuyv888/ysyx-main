// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__dpi_gprs__0 
        = vlSelfRef.top__DOT__dpi_gprs;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__dpi_gprs__1 
        = vlSelfRef.top__DOT__dpi_gprs;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);
VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    Vtop___024root____Vm_traceActivitySetAll(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__dpi_gprs[0U] = 0U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("test_all/vsrc_mem/top.v", 5, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
    if ((2ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 1 is active: @([hybrid] top.dpi_gprs)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf);
void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
        Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

void Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_write_TOP(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pc = vlSelfRef.top__DOT__pc_reg;
    vlSelfRef.a0 = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xaU];
    vlSelfRef.top__DOT__gpr__DOT__mcycle_total = (((QData)((IData)(vlSelfRef.top__DOT__gpr__DOT__mcycleh)) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(vlSelfRef.top__DOT__gpr__DOT__mcycle)));
    vlSelfRef.top__DOT__dpi_gprs[1U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [1U];
    vlSelfRef.top__DOT__dpi_gprs[2U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [2U];
    vlSelfRef.top__DOT__dpi_gprs[3U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [3U];
    vlSelfRef.top__DOT__dpi_gprs[4U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [4U];
    vlSelfRef.top__DOT__dpi_gprs[5U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [5U];
    vlSelfRef.top__DOT__dpi_gprs[6U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [6U];
    vlSelfRef.top__DOT__dpi_gprs[7U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [7U];
    vlSelfRef.top__DOT__dpi_gprs[8U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [8U];
    vlSelfRef.top__DOT__dpi_gprs[9U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [9U];
    vlSelfRef.top__DOT__dpi_gprs[0xaU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xaU];
    vlSelfRef.top__DOT__dpi_gprs[0xbU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xbU];
    vlSelfRef.top__DOT__dpi_gprs[0xcU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xcU];
    vlSelfRef.top__DOT__dpi_gprs[0xdU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xdU];
    vlSelfRef.top__DOT__dpi_gprs[0xeU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xeU];
    vlSelfRef.top__DOT__dpi_gprs[0xfU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xfU];
    vlSelfRef.top__DOT__dpi_gprs[0x10U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x10U];
    vlSelfRef.top__DOT__dpi_gprs[0x11U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x11U];
    vlSelfRef.top__DOT__dpi_gprs[0x12U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x12U];
    vlSelfRef.top__DOT__dpi_gprs[0x13U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x13U];
    vlSelfRef.top__DOT__dpi_gprs[0x14U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x14U];
    vlSelfRef.top__DOT__dpi_gprs[0x15U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x15U];
    vlSelfRef.top__DOT__dpi_gprs[0x16U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x16U];
    vlSelfRef.top__DOT__dpi_gprs[0x17U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x17U];
    vlSelfRef.top__DOT__dpi_gprs[0x18U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x18U];
    vlSelfRef.top__DOT__dpi_gprs[0x19U] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x19U];
    vlSelfRef.top__DOT__dpi_gprs[0x1aU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1aU];
    vlSelfRef.top__DOT__dpi_gprs[0x1bU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1bU];
    vlSelfRef.top__DOT__dpi_gprs[0x1cU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1cU];
    vlSelfRef.top__DOT__dpi_gprs[0x1dU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1dU];
    vlSelfRef.top__DOT__dpi_gprs[0x1eU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1eU];
    vlSelfRef.top__DOT__dpi_gprs[0x1fU] = vlSelfRef.top__DOT__gpr__DOT__rf
        [0x1fU];
    Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_read_TOP(vlSelfRef.top__DOT__pc_reg, vlSelfRef.__Vfunc_top__DOT__u_mem__DOT__pmem_read__1__Vfuncout);
    vlSelfRef.top__DOT__ifu_rdata = vlSelfRef.__Vfunc_top__DOT__u_mem__DOT__pmem_read__1__Vfuncout;
    vlSelfRef.inst = vlSelfRef.top__DOT__ifu_rdata;
    vlSelfRef.top__DOT__rd_addr = 0U;
    vlSelfRef.illegal_instruction = 0U;
    vlSelfRef.is_ebreak = 0U;
    vlSelfRef.top__DOT__is_csrrw = 0U;
    vlSelfRef.top__DOT__is_auipc = 0U;
    vlSelfRef.top__DOT__wen = 0U;
    vlSelfRef.top__DOT__csr_addr = 0U;
    vlSelfRef.top__DOT__is_addi = 0U;
    vlSelfRef.top__DOT__is_lui = 0U;
    vlSelfRef.top__DOT__is_lw = 0U;
    vlSelfRef.top__DOT__is_lbu = 0U;
    vlSelfRef.top__DOT__is_jalr = 0U;
    vlSelfRef.top__DOT__is_add = 0U;
    vlSelfRef.top__DOT__is_sw = 0U;
    vlSelfRef.top__DOT__is_sb = 0U;
    vlSelfRef.top__DOT__rs2_addr = 0U;
    vlSelfRef.top__DOT__mem_wen = 0U;
    vlSelfRef.top__DOT__mem_valid = 0U;
    vlSelfRef.top__DOT__rs1_addr = 0U;
    if ((1U & (~ (IData)(vlSelfRef.rst)))) {
        if (((((((((0x33U == (0xfe00707fU & vlSelfRef.inst)) 
                   | (0x13U == (0x707fU & vlSelfRef.inst))) 
                  | (0x37U == (0x7fU & vlSelfRef.inst))) 
                 | (0x2003U == (0x707fU & vlSelfRef.inst))) 
                | (0x4003U == (0x707fU & vlSelfRef.inst))) 
               | (0x2023U == (0x707fU & vlSelfRef.inst))) 
              | (0x23U == (0x707fU & vlSelfRef.inst))) 
             | (0x67U == (0x707fU & vlSelfRef.inst)))) {
            if ((0x33U == (0xfe00707fU & vlSelfRef.inst))) {
                vlSelfRef.top__DOT__rd_addr = (0x1fU 
                                               & (vlSelfRef.inst 
                                                  >> 7U));
                vlSelfRef.top__DOT__wen = 1U;
                vlSelfRef.top__DOT__is_add = 1U;
                vlSelfRef.top__DOT__rs2_addr = (0x1fU 
                                                & (vlSelfRef.inst 
                                                   >> 0x14U));
                vlSelfRef.top__DOT__rs1_addr = (0x1fU 
                                                & (vlSelfRef.inst 
                                                   >> 0xfU));
            } else {
                if ((0x13U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__rd_addr = (0x1fU 
                                                   & (vlSelfRef.inst 
                                                      >> 7U));
                    vlSelfRef.top__DOT__wen = 1U;
                    vlSelfRef.top__DOT__rs1_addr = 
                        (0x1fU & (vlSelfRef.inst >> 0xfU));
                } else {
                    if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.top__DOT__rd_addr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                        vlSelfRef.top__DOT__wen = 1U;
                    } else if ((0x2003U == (0x707fU 
                                            & vlSelfRef.inst))) {
                        vlSelfRef.top__DOT__rd_addr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                        vlSelfRef.top__DOT__wen = 1U;
                    } else if ((0x4003U == (0x707fU 
                                            & vlSelfRef.inst))) {
                        vlSelfRef.top__DOT__rd_addr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                        vlSelfRef.top__DOT__wen = 1U;
                    } else if ((0x2023U != (0x707fU 
                                            & vlSelfRef.inst))) {
                        if ((0x23U != (0x707fU & vlSelfRef.inst))) {
                            vlSelfRef.top__DOT__rd_addr 
                                = (0x1fU & (vlSelfRef.inst 
                                            >> 7U));
                            vlSelfRef.top__DOT__wen = 1U;
                        }
                    }
                    if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.top__DOT__rs1_addr 
                            = (0x1fU & ((0x2003U == 
                                         (0x707fU & vlSelfRef.inst))
                                         ? (vlSelfRef.inst 
                                            >> 0xfU)
                                         : ((0x4003U 
                                             == (0x707fU 
                                                 & vlSelfRef.inst))
                                             ? (vlSelfRef.inst 
                                                >> 0xfU)
                                             : ((0x2023U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelfRef.inst))
                                                 ? 
                                                (vlSelfRef.inst 
                                                 >> 0xfU)
                                                 : 
                                                ((0x23U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelfRef.inst))
                                                  ? 
                                                 (vlSelfRef.inst 
                                                  >> 0xfU)
                                                  : 
                                                 (vlSelfRef.inst 
                                                  >> 0xfU))))));
                    }
                }
                if ((0x13U != (0x707fU & vlSelfRef.inst))) {
                    if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                        if ((0x2003U != (0x707fU & vlSelfRef.inst))) {
                            if ((0x4003U != (0x707fU 
                                             & vlSelfRef.inst))) {
                                if ((0x2023U == (0x707fU 
                                                 & vlSelfRef.inst))) {
                                    vlSelfRef.top__DOT__rs2_addr 
                                        = (0x1fU & 
                                           (vlSelfRef.inst 
                                            >> 0x14U));
                                } else if ((0x23U == 
                                            (0x707fU 
                                             & vlSelfRef.inst))) {
                                    vlSelfRef.top__DOT__rs2_addr 
                                        = (0x1fU & 
                                           (vlSelfRef.inst 
                                            >> 0x14U));
                                }
                            }
                        }
                    }
                }
            }
            if ((0x33U != (0xfe00707fU & vlSelfRef.inst))) {
                if ((0x13U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__is_addi = 1U;
                }
                if ((0x13U != (0x707fU & vlSelfRef.inst))) {
                    if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.top__DOT__is_lui = 1U;
                    }
                    if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                        if ((0x2003U == (0x707fU & vlSelfRef.inst))) {
                            vlSelfRef.top__DOT__is_lw = 1U;
                            vlSelfRef.top__DOT__mem_valid = 1U;
                        } else if ((0x4003U == (0x707fU 
                                                & vlSelfRef.inst))) {
                            vlSelfRef.top__DOT__mem_valid = 1U;
                        } else if ((0x2023U == (0x707fU 
                                                & vlSelfRef.inst))) {
                            vlSelfRef.top__DOT__mem_valid = 1U;
                        } else if ((0x23U == (0x707fU 
                                              & vlSelfRef.inst))) {
                            vlSelfRef.top__DOT__mem_valid = 1U;
                        }
                        if ((0x2003U != (0x707fU & vlSelfRef.inst))) {
                            if ((0x4003U == (0x707fU 
                                             & vlSelfRef.inst))) {
                                vlSelfRef.top__DOT__is_lbu = 1U;
                            }
                            if ((0x4003U != (0x707fU 
                                             & vlSelfRef.inst))) {
                                if ((0x2023U != (0x707fU 
                                                 & vlSelfRef.inst))) {
                                    if ((0x23U != (0x707fU 
                                                   & vlSelfRef.inst))) {
                                        vlSelfRef.top__DOT__is_jalr = 1U;
                                    }
                                    if ((0x23U == (0x707fU 
                                                   & vlSelfRef.inst))) {
                                        vlSelfRef.top__DOT__is_sb = 1U;
                                    }
                                }
                                if ((0x2023U == (0x707fU 
                                                 & vlSelfRef.inst))) {
                                    vlSelfRef.top__DOT__is_sw = 1U;
                                    vlSelfRef.top__DOT__mem_wen = 1U;
                                } else if ((0x23U == 
                                            (0x707fU 
                                             & vlSelfRef.inst))) {
                                    vlSelfRef.top__DOT__mem_wen = 1U;
                                }
                            }
                        }
                    }
                }
            }
        } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
            vlSelfRef.top__DOT__rd_addr = (0x1fU & 
                                           (vlSelfRef.inst 
                                            >> 7U));
            vlSelfRef.top__DOT__wen = 1U;
        } else if ((0x1073U == (0x707fU & vlSelfRef.inst))) {
            vlSelfRef.top__DOT__rd_addr = (0x1fU & 
                                           (vlSelfRef.inst 
                                            >> 7U));
            vlSelfRef.top__DOT__wen = 1U;
        }
        if ((1U & (~ ((((((((0x33U == (0xfe00707fU 
                                       & vlSelfRef.inst)) 
                            | (0x13U == (0x707fU & vlSelfRef.inst))) 
                           | (0x37U == (0x7fU & vlSelfRef.inst))) 
                          | (0x2003U == (0x707fU & vlSelfRef.inst))) 
                         | (0x4003U == (0x707fU & vlSelfRef.inst))) 
                        | (0x2023U == (0x707fU & vlSelfRef.inst))) 
                       | (0x23U == (0x707fU & vlSelfRef.inst))) 
                      | (0x67U == (0x707fU & vlSelfRef.inst)))))) {
            if ((0x17U != (0x7fU & vlSelfRef.inst))) {
                if ((0x1073U != (0x707fU & vlSelfRef.inst))) {
                    if ((0x100073U != vlSelfRef.inst)) {
                        vlSelfRef.illegal_instruction 
                            = ((0U == vlSelfRef.inst)
                                ? 0U : 1U);
                    }
                    vlSelfRef.is_ebreak = ((0x100073U 
                                            == vlSelfRef.inst) 
                                           || ((0U 
                                                == vlSelfRef.inst)
                                                ? 0U
                                                : 1U));
                }
                if ((0x1073U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__is_csrrw = 1U;
                    vlSelfRef.top__DOT__csr_addr = 
                        (0x1fU & (vlSelfRef.inst >> 0xfU));
                }
            }
            if ((0x17U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.top__DOT__is_auipc = 1U;
            }
        }
    }
    vlSelfRef.top__DOT__rs1_data = ((0U == (IData)(vlSelfRef.top__DOT__rs1_addr))
                                     ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                    [vlSelfRef.top__DOT__rs1_addr]);
    vlSelfRef.top__DOT__u_exu__DOT__wdata_add = ((IData)(vlSelfRef.top__DOT__is_add)
                                                  ? 
                                                 (vlSelfRef.top__DOT__rs1_data 
                                                  + 
                                                  ((0U 
                                                    == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                                    ? 0U
                                                    : 
                                                   vlSelfRef.top__DOT__gpr__DOT__rf
                                                   [vlSelfRef.top__DOT__rs2_addr]))
                                                  : 0U);
    vlSelfRef.top__DOT__imm = 0U;
    vlSelfRef.top__DOT__mem_addr = 0U;
    vlSelfRef.top__DOT__mem_wmask = 0U;
    if ((1U & (~ (IData)(vlSelfRef.rst)))) {
        if (((((((((0x33U == (0xfe00707fU & vlSelfRef.inst)) 
                   | (0x13U == (0x707fU & vlSelfRef.inst))) 
                  | (0x37U == (0x7fU & vlSelfRef.inst))) 
                 | (0x2003U == (0x707fU & vlSelfRef.inst))) 
                | (0x4003U == (0x707fU & vlSelfRef.inst))) 
               | (0x2023U == (0x707fU & vlSelfRef.inst))) 
              | (0x23U == (0x707fU & vlSelfRef.inst))) 
             | (0x67U == (0x707fU & vlSelfRef.inst)))) {
            if ((0x33U != (0xfe00707fU & vlSelfRef.inst))) {
                if ((0x13U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | (vlSelfRef.inst 
                                                  >> 0x14U));
                } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (0xfffff000U 
                                               & vlSelfRef.inst);
                } else if ((0x2003U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | (vlSelfRef.inst 
                                                  >> 0x14U));
                    vlSelfRef.top__DOT__mem_addr = 
                        (vlSelfRef.top__DOT__rs1_data 
                         + vlSelfRef.top__DOT__imm);
                } else if ((0x4003U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | (vlSelfRef.inst 
                                                  >> 0x14U));
                    vlSelfRef.top__DOT__mem_addr = 
                        (vlSelfRef.top__DOT__rs1_data 
                         + vlSelfRef.top__DOT__imm);
                } else if ((0x2023U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | ((0xfe0U 
                                                   & (vlSelfRef.inst 
                                                      >> 0x14U)) 
                                                  | (0x1fU 
                                                     & (vlSelfRef.inst 
                                                        >> 7U))));
                    vlSelfRef.top__DOT__mem_addr = 
                        (vlSelfRef.top__DOT__rs1_data 
                         + vlSelfRef.top__DOT__imm);
                    vlSelfRef.top__DOT__mem_wmask = 0xfU;
                } else if ((0x23U == (0x707fU & vlSelfRef.inst))) {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | ((0xfe0U 
                                                   & (vlSelfRef.inst 
                                                      >> 0x14U)) 
                                                  | (0x1fU 
                                                     & (vlSelfRef.inst 
                                                        >> 7U))));
                    vlSelfRef.top__DOT__mem_addr = 
                        (vlSelfRef.top__DOT__rs1_data 
                         + vlSelfRef.top__DOT__imm);
                    vlSelfRef.top__DOT__mem_wmask = 
                        (0xfU & ((IData)(1U) << (3U 
                                                 & vlSelfRef.top__DOT__mem_addr)));
                } else {
                    vlSelfRef.top__DOT__imm = (((- (IData)(
                                                           (vlSelfRef.inst 
                                                            >> 0x1fU))) 
                                                << 0xcU) 
                                               | (vlSelfRef.inst 
                                                  >> 0x14U));
                }
            }
        } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
            vlSelfRef.top__DOT__imm = (0xfffff000U 
                                       & vlSelfRef.inst);
        }
    }
    vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0 
        = (vlSelfRef.top__DOT__imm + vlSelfRef.top__DOT__rs1_data);
    if (vlSelfRef.top__DOT__mem_valid) {
        if (vlSelfRef.top__DOT__mem_wen) {
            vlSelfRef.top__DOT__lsu_rdata = 0U;
        } else {
            Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_read_TOP(vlSelfRef.top__DOT__mem_addr, vlSelfRef.__Vfunc_top__DOT__u_mem__DOT__pmem_read__2__Vfuncout);
            vlSelfRef.top__DOT__lsu_rdata = vlSelfRef.__Vfunc_top__DOT__u_mem__DOT__pmem_read__2__Vfuncout;
        }
    }
    if (((IData)(vlSelfRef.top__DOT__mem_wen) & (IData)(vlSelfRef.top__DOT__mem_valid))) {
        Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_write_TOP(vlSelfRef.top__DOT__mem_addr, 
                                                                          ((IData)(vlSelfRef.top__DOT__is_sw)
                                                                            ? 
                                                                           ((0U 
                                                                             == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                                                             ? 0U
                                                                             : 
                                                                            vlSelfRef.top__DOT__gpr__DOT__rf
                                                                            [vlSelfRef.top__DOT__rs2_addr])
                                                                            : 
                                                                           ((IData)(vlSelfRef.top__DOT__is_sb)
                                                                             ? 
                                                                            ((0U 
                                                                              == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                                                              ? 0U
                                                                              : 
                                                                             (0xffU 
                                                                              & vlSelfRef.top__DOT__gpr__DOT__rf
                                                                              [vlSelfRef.top__DOT__rs2_addr]))
                                                                             : 0U)), (IData)(vlSelfRef.top__DOT__mem_wmask));
    }
    vlSelfRef.top__DOT__u_wbu__DOT__pc_dnpc = ((IData)(vlSelfRef.top__DOT__is_jalr)
                                                ? ((IData)(vlSelfRef.top__DOT__is_jalr)
                                                    ? 
                                                   (0xfffffffeU 
                                                    & vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0)
                                                    : 0U)
                                                : ((IData)(4U) 
                                                   + vlSelfRef.top__DOT__pc_reg));
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @([hybrid] top.dpi_gprs)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
    if ((4ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @(posedge rst)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @([hybrid] top.dpi_gprs)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
    if ((4ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @(posedge rst)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vm_traceActivitySetAll\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.__Vm_traceActivity[3U] = 1U;
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9812503827101699671ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4211327832146562899ull);
    vlSelf->a0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17342812819118991936ull);
    vlSelf->is_ebreak = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17481212467687349763ull);
    vlSelf->illegal_instruction = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1918813271126014492ull);
    vlSelf->top__DOT__rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 595039983895368829ull);
    vlSelf->top__DOT__imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18445623346312568628ull);
    vlSelf->top__DOT__pc_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9558982966795960158ull);
    vlSelf->top__DOT__mem_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10369574258756297708ull);
    vlSelf->top__DOT__is_add = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2607680469840166300ull);
    vlSelf->top__DOT__is_addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8314111965283110266ull);
    vlSelf->top__DOT__is_lui = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6253517582979062719ull);
    vlSelf->top__DOT__is_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17792527757510442866ull);
    vlSelf->top__DOT__is_lbu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18204020040551684123ull);
    vlSelf->top__DOT__is_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7239518796479858432ull);
    vlSelf->top__DOT__is_sb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4655499176252229976ull);
    vlSelf->top__DOT__is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13225455105894283407ull);
    vlSelf->top__DOT__is_auipc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6903679913796685481ull);
    vlSelf->top__DOT__is_csrrw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12983363925745937194ull);
    vlSelf->top__DOT__inst_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16965637627309696195ull);
    vlSelf->top__DOT__wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5718604826377190525ull);
    vlSelf->top__DOT__rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9485048292088896507ull);
    vlSelf->top__DOT__rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3295586838479721231ull);
    vlSelf->top__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3787934847675002855ull);
    vlSelf->top__DOT__csr_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12351374403152066878ull);
    vlSelf->top__DOT__mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12982821084159389865ull);
    vlSelf->top__DOT__mem_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17082788271205367820ull);
    vlSelf->top__DOT__mem_wmask = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7024006030315882635ull);
    vlSelf->top__DOT__ifu_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2772403880220773911ull);
    vlSelf->top__DOT__lsu_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5717850918461618104ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__dpi_gprs[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4287205387284412661ull);
    }
    vlSelf->top__DOT__u_exu__DOT__wdata_add = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12381254110778202891ull);
    vlSelf->top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14373284162120373057ull);
    vlSelf->top__DOT__u_wbu__DOT__pc_dnpc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5859803910380112307ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__gpr__DOT__rf[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16382366690009327570ull);
    }
    vlSelf->top__DOT__gpr__DOT__mcycle = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3037911999505914819ull);
    vlSelf->top__DOT__gpr__DOT__mcycleh = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 166059431374608893ull);
    vlSelf->top__DOT__gpr__DOT__mvendorid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17761740142646150098ull);
    vlSelf->top__DOT__gpr__DOT__marchid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9502777755805155344ull);
    vlSelf->top__DOT__gpr__DOT__mcycle_total = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8064111346599641450ull);
    vlSelf->__Vfunc_top__DOT__u_mem__DOT__pmem_read__1__Vfuncout = 0;
    vlSelf->__Vfunc_top__DOT__u_mem__DOT__pmem_read__2__Vfuncout = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->__Vtrigprevexpr___TOP__top__DOT__dpi_gprs__0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14177609652592997634ull);
    }
    vlSelf->__VstlDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->__Vtrigprevexpr___TOP__top__DOT__dpi_gprs__1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13344958017492793071ull);
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3495601893105415319ull);
    vlSelf->__VactDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 5; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
