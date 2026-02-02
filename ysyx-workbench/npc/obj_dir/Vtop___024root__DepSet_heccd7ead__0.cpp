// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

void Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vtop___024root____Vdpiimwrap_top__DOT__u_mem__DOT__pmem_write_TOP(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
}

VL_INLINE_OPT void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___act_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__dpi_gprs[0U] = vlSelfRef.top__DOT__dpi_gprs
        [0U];
    vlSelfRef.top__DOT__dpi_gprs[1U] = vlSelfRef.top__DOT__dpi_gprs
        [1U];
    vlSelfRef.top__DOT__dpi_gprs[2U] = vlSelfRef.top__DOT__dpi_gprs
        [2U];
    vlSelfRef.top__DOT__dpi_gprs[3U] = vlSelfRef.top__DOT__dpi_gprs
        [3U];
    vlSelfRef.top__DOT__dpi_gprs[4U] = vlSelfRef.top__DOT__dpi_gprs
        [4U];
    vlSelfRef.top__DOT__dpi_gprs[5U] = vlSelfRef.top__DOT__dpi_gprs
        [5U];
    vlSelfRef.top__DOT__dpi_gprs[6U] = vlSelfRef.top__DOT__dpi_gprs
        [6U];
    vlSelfRef.top__DOT__dpi_gprs[7U] = vlSelfRef.top__DOT__dpi_gprs
        [7U];
    vlSelfRef.top__DOT__dpi_gprs[8U] = vlSelfRef.top__DOT__dpi_gprs
        [8U];
    vlSelfRef.top__DOT__dpi_gprs[9U] = vlSelfRef.top__DOT__dpi_gprs
        [9U];
    vlSelfRef.top__DOT__dpi_gprs[0xaU] = vlSelfRef.top__DOT__dpi_gprs
        [0xaU];
    vlSelfRef.top__DOT__dpi_gprs[0xbU] = vlSelfRef.top__DOT__dpi_gprs
        [0xbU];
    vlSelfRef.top__DOT__dpi_gprs[0xcU] = vlSelfRef.top__DOT__dpi_gprs
        [0xcU];
    vlSelfRef.top__DOT__dpi_gprs[0xdU] = vlSelfRef.top__DOT__dpi_gprs
        [0xdU];
    vlSelfRef.top__DOT__dpi_gprs[0xeU] = vlSelfRef.top__DOT__dpi_gprs
        [0xeU];
    vlSelfRef.top__DOT__dpi_gprs[0xfU] = vlSelfRef.top__DOT__dpi_gprs
        [0xfU];
    vlSelfRef.top__DOT__dpi_gprs[0x10U] = vlSelfRef.top__DOT__dpi_gprs
        [0x10U];
    vlSelfRef.top__DOT__dpi_gprs[0x11U] = vlSelfRef.top__DOT__dpi_gprs
        [0x11U];
    vlSelfRef.top__DOT__dpi_gprs[0x12U] = vlSelfRef.top__DOT__dpi_gprs
        [0x12U];
    vlSelfRef.top__DOT__dpi_gprs[0x13U] = vlSelfRef.top__DOT__dpi_gprs
        [0x13U];
    vlSelfRef.top__DOT__dpi_gprs[0x14U] = vlSelfRef.top__DOT__dpi_gprs
        [0x14U];
    vlSelfRef.top__DOT__dpi_gprs[0x15U] = vlSelfRef.top__DOT__dpi_gprs
        [0x15U];
    vlSelfRef.top__DOT__dpi_gprs[0x16U] = vlSelfRef.top__DOT__dpi_gprs
        [0x16U];
    vlSelfRef.top__DOT__dpi_gprs[0x17U] = vlSelfRef.top__DOT__dpi_gprs
        [0x17U];
    vlSelfRef.top__DOT__dpi_gprs[0x18U] = vlSelfRef.top__DOT__dpi_gprs
        [0x18U];
    vlSelfRef.top__DOT__dpi_gprs[0x19U] = vlSelfRef.top__DOT__dpi_gprs
        [0x19U];
    vlSelfRef.top__DOT__dpi_gprs[0x1aU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1aU];
    vlSelfRef.top__DOT__dpi_gprs[0x1bU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1bU];
    vlSelfRef.top__DOT__dpi_gprs[0x1cU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1cU];
    vlSelfRef.top__DOT__dpi_gprs[0x1dU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1dU];
    vlSelfRef.top__DOT__dpi_gprs[0x1eU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1eU];
    vlSelfRef.top__DOT__dpi_gprs[0x1fU] = vlSelfRef.top__DOT__dpi_gprs
        [0x1fU];
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);
void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf);
void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        Vtop___024root___nba_comb__TOP__0(vlSelf);
    }
}

void Vtop___024root____Vdpiimwrap_top__DOT__dpi_get_gprs_TOP(VlUnpacked<IData/*31:0*/, 32> gprs, IData/*31:0*/ pc_reg);

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__top__DOT__gpr__DOT__rf__v0;
    __VdlyVal__top__DOT__gpr__DOT__rf__v0 = 0;
    CData/*4:0*/ __VdlyDim0__top__DOT__gpr__DOT__rf__v0;
    __VdlyDim0__top__DOT__gpr__DOT__rf__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__gpr__DOT__rf__v0;
    __VdlySet__top__DOT__gpr__DOT__rf__v0 = 0;
    // Body
    if ((1U & (~ (IData)(vlSelfRef.rst)))) {
        Vtop___024root____Vdpiimwrap_top__DOT__dpi_get_gprs_TOP(vlSelfRef.top__DOT__dpi_gprs, vlSelfRef.top__DOT__pc_reg);
    }
    __VdlySet__top__DOT__gpr__DOT__rf__v0 = 0U;
    if (((IData)(vlSelfRef.top__DOT__wen) & (0U != (IData)(vlSelfRef.top__DOT__rd_addr)))) {
        __VdlyVal__top__DOT__gpr__DOT__rf__v0 = ((IData)(vlSelfRef.top__DOT__is_add)
                                                  ? vlSelfRef.top__DOT__u_exu__DOT__wdata_add
                                                  : 
                                                 ((IData)(vlSelfRef.top__DOT__is_addi)
                                                   ? 
                                                  ((IData)(vlSelfRef.top__DOT__is_addi)
                                                    ? vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0
                                                    : 0U)
                                                   : 
                                                  ((IData)(vlSelfRef.top__DOT__is_lui)
                                                    ? 
                                                   ((IData)(vlSelfRef.top__DOT__is_lui)
                                                     ? vlSelfRef.top__DOT__imm
                                                     : 0U)
                                                    : 
                                                   ((IData)(vlSelfRef.top__DOT__is_lw)
                                                     ? 
                                                    ((IData)(vlSelfRef.top__DOT__is_lw)
                                                      ? vlSelfRef.top__DOT__lsu_rdata
                                                      : 0U)
                                                     : 
                                                    ((IData)(vlSelfRef.top__DOT__is_lbu)
                                                      ? 
                                                     ((IData)(vlSelfRef.top__DOT__is_lbu)
                                                       ? 
                                                      (0xffU 
                                                       & ((2U 
                                                           & vlSelfRef.top__DOT__mem_addr)
                                                           ? 
                                                          ((1U 
                                                            & vlSelfRef.top__DOT__mem_addr)
                                                            ? 
                                                           (vlSelfRef.top__DOT__lsu_rdata 
                                                            >> 0x18U)
                                                            : 
                                                           (vlSelfRef.top__DOT__lsu_rdata 
                                                            >> 0x10U))
                                                           : 
                                                          ((1U 
                                                            & vlSelfRef.top__DOT__mem_addr)
                                                            ? 
                                                           (vlSelfRef.top__DOT__lsu_rdata 
                                                            >> 8U)
                                                            : vlSelfRef.top__DOT__lsu_rdata)))
                                                       : 0U)
                                                      : 
                                                     ((IData)(vlSelfRef.top__DOT__is_jalr)
                                                       ? 
                                                      ((IData)(4U) 
                                                       + vlSelfRef.top__DOT__pc_reg)
                                                       : 
                                                      ((IData)(vlSelfRef.top__DOT__is_auipc)
                                                        ? 
                                                       (vlSelfRef.top__DOT__imm 
                                                        + vlSelfRef.top__DOT__pc_reg)
                                                        : 
                                                       ((IData)(vlSelfRef.top__DOT__is_csrrw)
                                                         ? 
                                                        ((IData)(vlSelfRef.top__DOT__is_csrrw)
                                                          ? vlSelfRef.top__DOT__rs1_data
                                                          : 0U)
                                                         : 0U))))))));
        __VdlyDim0__top__DOT__gpr__DOT__rf__v0 = vlSelfRef.top__DOT__rd_addr;
        __VdlySet__top__DOT__gpr__DOT__rf__v0 = 1U;
    }
    if (__VdlySet__top__DOT__gpr__DOT__rf__v0) {
        vlSelfRef.top__DOT__gpr__DOT__rf[__VdlyDim0__top__DOT__gpr__DOT__rf__v0] 
            = __VdlyVal__top__DOT__gpr__DOT__rf__v0;
    }
    vlSelfRef.a0 = vlSelfRef.top__DOT__gpr__DOT__rf
        [0xaU];
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
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.rst) {
        vlSelfRef.top__DOT__gpr__DOT__mvendorid = 0x79737978U;
        vlSelfRef.top__DOT__gpr__DOT__marchid = 0x17eb18fU;
        vlSelfRef.top__DOT__gpr__DOT__mcycle = 0U;
        vlSelfRef.top__DOT__gpr__DOT__mcycleh = 0U;
        vlSelfRef.top__DOT__pc_reg = 0x80000000U;
    } else {
        vlSelfRef.top__DOT__gpr__DOT__mcycle = ((IData)(1U) 
                                                + (IData)(vlSelfRef.top__DOT__gpr__DOT__mcycle_total));
        vlSelfRef.top__DOT__gpr__DOT__mcycleh = (IData)(
                                                        ((1ULL 
                                                          + vlSelfRef.top__DOT__gpr__DOT__mcycle_total) 
                                                         >> 0x20U));
        vlSelfRef.top__DOT__pc_reg = vlSelfRef.top__DOT__u_wbu__DOT__pc_dnpc;
    }
    vlSelfRef.top__DOT__gpr__DOT__mcycle_total = (((QData)((IData)(vlSelfRef.top__DOT__gpr__DOT__mcycleh)) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(vlSelfRef.top__DOT__gpr__DOT__mcycle)));
    vlSelfRef.pc = vlSelfRef.top__DOT__pc_reg;
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
}

VL_INLINE_OPT void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("test_all/vsrc_mem/top.v", 5, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("test_all/vsrc_mem/top.v", 5, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("test_all/vsrc_mem/top.v", 5, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
