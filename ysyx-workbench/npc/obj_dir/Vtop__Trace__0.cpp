// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity
                      [4U])))) {
        bufp->chgIData(oldp+0,(vlSelfRef.top__DOT__rs1_data),32);
        bufp->chgIData(oldp+1,(vlSelfRef.top__DOT__imm),32);
        bufp->chgIData(oldp+2,(vlSelfRef.top__DOT__lsu_rdata),32);
        bufp->chgIData(oldp+3,(vlSelfRef.top__DOT__mem_addr),32);
        bufp->chgBit(oldp+4,(vlSelfRef.top__DOT__is_add));
        bufp->chgBit(oldp+5,(vlSelfRef.top__DOT__is_addi));
        bufp->chgBit(oldp+6,(vlSelfRef.top__DOT__is_lui));
        bufp->chgBit(oldp+7,(vlSelfRef.top__DOT__is_lw));
        bufp->chgBit(oldp+8,(vlSelfRef.top__DOT__is_lbu));
        bufp->chgBit(oldp+9,(vlSelfRef.top__DOT__is_sw));
        bufp->chgBit(oldp+10,(vlSelfRef.top__DOT__is_sb));
        bufp->chgBit(oldp+11,(vlSelfRef.top__DOT__is_jalr));
        bufp->chgBit(oldp+12,(vlSelfRef.top__DOT__is_auipc));
        bufp->chgBit(oldp+13,(vlSelfRef.top__DOT__is_csrrw));
        bufp->chgIData(oldp+14,(((IData)(vlSelfRef.top__DOT__is_jalr)
                                  ? (0xfffffffeU & vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0)
                                  : 0U)),32);
        bufp->chgBit(oldp+15,(vlSelfRef.top__DOT__wen));
        bufp->chgCData(oldp+16,(vlSelfRef.top__DOT__rs1_addr),5);
        bufp->chgCData(oldp+17,(vlSelfRef.top__DOT__rs2_addr),5);
        bufp->chgCData(oldp+18,(vlSelfRef.top__DOT__rd_addr),5);
        bufp->chgCData(oldp+19,(vlSelfRef.top__DOT__csr_addr),5);
        bufp->chgBit(oldp+20,(vlSelfRef.top__DOT__mem_valid));
        bufp->chgBit(oldp+21,(vlSelfRef.top__DOT__mem_wen));
        bufp->chgCData(oldp+22,(vlSelfRef.top__DOT__mem_wmask),4);
        bufp->chgIData(oldp+23,(((IData)(vlSelfRef.top__DOT__is_addi)
                                  ? vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0
                                  : 0U)),32);
        bufp->chgIData(oldp+24,(((IData)(vlSelfRef.top__DOT__is_lui)
                                  ? vlSelfRef.top__DOT__imm
                                  : 0U)),32);
        bufp->chgIData(oldp+25,(((IData)(vlSelfRef.top__DOT__is_lw)
                                  ? vlSelfRef.top__DOT__lsu_rdata
                                  : 0U)),32);
        bufp->chgIData(oldp+26,(((IData)(vlSelfRef.top__DOT__is_lbu)
                                  ? (0xffU & ((2U & vlSelfRef.top__DOT__mem_addr)
                                               ? ((1U 
                                                   & vlSelfRef.top__DOT__mem_addr)
                                                   ? 
                                                  (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 0x18U)
                                                   : 
                                                  (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 0x10U))
                                               : ((1U 
                                                   & vlSelfRef.top__DOT__mem_addr)
                                                   ? 
                                                  (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 8U)
                                                   : vlSelfRef.top__DOT__lsu_rdata)))
                                  : 0U)),32);
        bufp->chgIData(oldp+27,((vlSelfRef.top__DOT__imm 
                                 + vlSelfRef.top__DOT__pc_reg)),32);
        bufp->chgIData(oldp+28,(((IData)(vlSelfRef.top__DOT__is_csrrw)
                                  ? vlSelfRef.top__DOT__rs1_data
                                  : 0U)),32);
        bufp->chgCData(oldp+29,((0xffU & ((2U & vlSelfRef.top__DOT__mem_addr)
                                           ? ((1U & vlSelfRef.top__DOT__mem_addr)
                                               ? (vlSelfRef.top__DOT__lsu_rdata 
                                                  >> 0x18U)
                                               : (vlSelfRef.top__DOT__lsu_rdata 
                                                  >> 0x10U))
                                           : ((1U & vlSelfRef.top__DOT__mem_addr)
                                               ? (vlSelfRef.top__DOT__lsu_rdata 
                                                  >> 8U)
                                               : vlSelfRef.top__DOT__lsu_rdata)))),8);
        bufp->chgIData(oldp+30,(((IData)(vlSelfRef.top__DOT__is_jalr)
                                  ? ((IData)(vlSelfRef.top__DOT__is_jalr)
                                      ? (0xfffffffeU 
                                         & vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0)
                                      : 0U) : ((IData)(4U) 
                                               + vlSelfRef.top__DOT__pc_reg))),32);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[2U] 
                      | vlSelfRef.__Vm_traceActivity
                      [3U])))) {
        bufp->chgIData(oldp+31,(vlSelfRef.top__DOT__dpi_gprs[0]),32);
        bufp->chgIData(oldp+32,(vlSelfRef.top__DOT__dpi_gprs[1]),32);
        bufp->chgIData(oldp+33,(vlSelfRef.top__DOT__dpi_gprs[2]),32);
        bufp->chgIData(oldp+34,(vlSelfRef.top__DOT__dpi_gprs[3]),32);
        bufp->chgIData(oldp+35,(vlSelfRef.top__DOT__dpi_gprs[4]),32);
        bufp->chgIData(oldp+36,(vlSelfRef.top__DOT__dpi_gprs[5]),32);
        bufp->chgIData(oldp+37,(vlSelfRef.top__DOT__dpi_gprs[6]),32);
        bufp->chgIData(oldp+38,(vlSelfRef.top__DOT__dpi_gprs[7]),32);
        bufp->chgIData(oldp+39,(vlSelfRef.top__DOT__dpi_gprs[8]),32);
        bufp->chgIData(oldp+40,(vlSelfRef.top__DOT__dpi_gprs[9]),32);
        bufp->chgIData(oldp+41,(vlSelfRef.top__DOT__dpi_gprs[10]),32);
        bufp->chgIData(oldp+42,(vlSelfRef.top__DOT__dpi_gprs[11]),32);
        bufp->chgIData(oldp+43,(vlSelfRef.top__DOT__dpi_gprs[12]),32);
        bufp->chgIData(oldp+44,(vlSelfRef.top__DOT__dpi_gprs[13]),32);
        bufp->chgIData(oldp+45,(vlSelfRef.top__DOT__dpi_gprs[14]),32);
        bufp->chgIData(oldp+46,(vlSelfRef.top__DOT__dpi_gprs[15]),32);
        bufp->chgIData(oldp+47,(vlSelfRef.top__DOT__dpi_gprs[16]),32);
        bufp->chgIData(oldp+48,(vlSelfRef.top__DOT__dpi_gprs[17]),32);
        bufp->chgIData(oldp+49,(vlSelfRef.top__DOT__dpi_gprs[18]),32);
        bufp->chgIData(oldp+50,(vlSelfRef.top__DOT__dpi_gprs[19]),32);
        bufp->chgIData(oldp+51,(vlSelfRef.top__DOT__dpi_gprs[20]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.top__DOT__dpi_gprs[21]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.top__DOT__dpi_gprs[22]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.top__DOT__dpi_gprs[23]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.top__DOT__dpi_gprs[24]),32);
        bufp->chgIData(oldp+56,(vlSelfRef.top__DOT__dpi_gprs[25]),32);
        bufp->chgIData(oldp+57,(vlSelfRef.top__DOT__dpi_gprs[26]),32);
        bufp->chgIData(oldp+58,(vlSelfRef.top__DOT__dpi_gprs[27]),32);
        bufp->chgIData(oldp+59,(vlSelfRef.top__DOT__dpi_gprs[28]),32);
        bufp->chgIData(oldp+60,(vlSelfRef.top__DOT__dpi_gprs[29]),32);
        bufp->chgIData(oldp+61,(vlSelfRef.top__DOT__dpi_gprs[30]),32);
        bufp->chgIData(oldp+62,(vlSelfRef.top__DOT__dpi_gprs[31]),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgIData(oldp+63,(vlSelfRef.top__DOT__gpr__DOT__rf[0]),32);
        bufp->chgIData(oldp+64,(vlSelfRef.top__DOT__gpr__DOT__rf[1]),32);
        bufp->chgIData(oldp+65,(vlSelfRef.top__DOT__gpr__DOT__rf[2]),32);
        bufp->chgIData(oldp+66,(vlSelfRef.top__DOT__gpr__DOT__rf[3]),32);
        bufp->chgIData(oldp+67,(vlSelfRef.top__DOT__gpr__DOT__rf[4]),32);
        bufp->chgIData(oldp+68,(vlSelfRef.top__DOT__gpr__DOT__rf[5]),32);
        bufp->chgIData(oldp+69,(vlSelfRef.top__DOT__gpr__DOT__rf[6]),32);
        bufp->chgIData(oldp+70,(vlSelfRef.top__DOT__gpr__DOT__rf[7]),32);
        bufp->chgIData(oldp+71,(vlSelfRef.top__DOT__gpr__DOT__rf[8]),32);
        bufp->chgIData(oldp+72,(vlSelfRef.top__DOT__gpr__DOT__rf[9]),32);
        bufp->chgIData(oldp+73,(vlSelfRef.top__DOT__gpr__DOT__rf[10]),32);
        bufp->chgIData(oldp+74,(vlSelfRef.top__DOT__gpr__DOT__rf[11]),32);
        bufp->chgIData(oldp+75,(vlSelfRef.top__DOT__gpr__DOT__rf[12]),32);
        bufp->chgIData(oldp+76,(vlSelfRef.top__DOT__gpr__DOT__rf[13]),32);
        bufp->chgIData(oldp+77,(vlSelfRef.top__DOT__gpr__DOT__rf[14]),32);
        bufp->chgIData(oldp+78,(vlSelfRef.top__DOT__gpr__DOT__rf[15]),32);
        bufp->chgIData(oldp+79,(vlSelfRef.top__DOT__gpr__DOT__rf[16]),32);
        bufp->chgIData(oldp+80,(vlSelfRef.top__DOT__gpr__DOT__rf[17]),32);
        bufp->chgIData(oldp+81,(vlSelfRef.top__DOT__gpr__DOT__rf[18]),32);
        bufp->chgIData(oldp+82,(vlSelfRef.top__DOT__gpr__DOT__rf[19]),32);
        bufp->chgIData(oldp+83,(vlSelfRef.top__DOT__gpr__DOT__rf[20]),32);
        bufp->chgIData(oldp+84,(vlSelfRef.top__DOT__gpr__DOT__rf[21]),32);
        bufp->chgIData(oldp+85,(vlSelfRef.top__DOT__gpr__DOT__rf[22]),32);
        bufp->chgIData(oldp+86,(vlSelfRef.top__DOT__gpr__DOT__rf[23]),32);
        bufp->chgIData(oldp+87,(vlSelfRef.top__DOT__gpr__DOT__rf[24]),32);
        bufp->chgIData(oldp+88,(vlSelfRef.top__DOT__gpr__DOT__rf[25]),32);
        bufp->chgIData(oldp+89,(vlSelfRef.top__DOT__gpr__DOT__rf[26]),32);
        bufp->chgIData(oldp+90,(vlSelfRef.top__DOT__gpr__DOT__rf[27]),32);
        bufp->chgIData(oldp+91,(vlSelfRef.top__DOT__gpr__DOT__rf[28]),32);
        bufp->chgIData(oldp+92,(vlSelfRef.top__DOT__gpr__DOT__rf[29]),32);
        bufp->chgIData(oldp+93,(vlSelfRef.top__DOT__gpr__DOT__rf[30]),32);
        bufp->chgIData(oldp+94,(vlSelfRef.top__DOT__gpr__DOT__rf[31]),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[4U]))) {
        bufp->chgIData(oldp+95,(vlSelfRef.top__DOT__pc_reg),32);
        bufp->chgIData(oldp+96,(vlSelfRef.top__DOT__ifu_rdata),32);
        bufp->chgIData(oldp+97,(vlSelfRef.top__DOT__gpr__DOT__mcycle),32);
        bufp->chgIData(oldp+98,(vlSelfRef.top__DOT__gpr__DOT__mcycleh),32);
        bufp->chgIData(oldp+99,(vlSelfRef.top__DOT__gpr__DOT__mvendorid),32);
        bufp->chgIData(oldp+100,(vlSelfRef.top__DOT__gpr__DOT__marchid),32);
        bufp->chgQData(oldp+101,(vlSelfRef.top__DOT__gpr__DOT__mcycle_total),64);
        bufp->chgIData(oldp+103,(((IData)(4U) + vlSelfRef.top__DOT__pc_reg)),32);
    }
    bufp->chgBit(oldp+104,(vlSelfRef.clk));
    bufp->chgIData(oldp+105,(vlSelfRef.inst),32);
    bufp->chgBit(oldp+106,(vlSelfRef.rst));
    bufp->chgIData(oldp+107,(vlSelfRef.pc),32);
    bufp->chgIData(oldp+108,(vlSelfRef.a0),32);
    bufp->chgBit(oldp+109,(vlSelfRef.is_ebreak));
    bufp->chgBit(oldp+110,(vlSelfRef.illegal_instruction));
    bufp->chgIData(oldp+111,(((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                               ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                              [vlSelfRef.top__DOT__rs2_addr])),32);
    bufp->chgIData(oldp+112,(((IData)(vlSelfRef.top__DOT__is_add)
                               ? ((IData)(vlSelfRef.top__DOT__is_add)
                                   ? (vlSelfRef.top__DOT__rs1_data 
                                      + ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                          ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                         [vlSelfRef.top__DOT__rs2_addr]))
                                   : 0U) : ((IData)(vlSelfRef.top__DOT__is_addi)
                                             ? ((IData)(vlSelfRef.top__DOT__is_addi)
                                                 ? vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0
                                                 : 0U)
                                             : ((IData)(vlSelfRef.top__DOT__is_lui)
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
                                                      : 0U))))))))),32);
    bufp->chgIData(oldp+113,(((IData)(vlSelfRef.top__DOT__is_sw)
                               ? ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                   ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                  [vlSelfRef.top__DOT__rs2_addr])
                               : ((IData)(vlSelfRef.top__DOT__is_sb)
                                   ? ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                       ? 0U : (0xffU 
                                               & vlSelfRef.top__DOT__gpr__DOT__rf
                                               [vlSelfRef.top__DOT__rs2_addr]))
                                   : 0U))),32);
    bufp->chgIData(oldp+114,(((IData)(vlSelfRef.top__DOT__is_add)
                               ? (vlSelfRef.top__DOT__rs1_data 
                                  + ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                      ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                     [vlSelfRef.top__DOT__rs2_addr]))
                               : 0U)),32);
    bufp->chgIData(oldp+115,(((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                               ? 0U : (0xffU & vlSelfRef.top__DOT__gpr__DOT__rf
                                       [vlSelfRef.top__DOT__rs2_addr]))),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
}
