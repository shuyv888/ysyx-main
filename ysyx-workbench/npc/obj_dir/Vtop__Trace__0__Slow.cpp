// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+105,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+106,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+107,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+108,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+110,0,"is_ebreak",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"illegal_instruction",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+105,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+106,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+107,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+108,0,"pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+110,0,"is_ebreak",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"illegal_instruction",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+1,0,"rs1_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"rs2_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"pc_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+3,0,"mem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+117,0,"csr_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"mem_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"is_add",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"is_addi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"is_lui",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"is_lw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"is_lbu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"is_sw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"is_sb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"is_jalr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"is_auipc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"is_csrrw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+118,0,"inst_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+113,0,"wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+114,0,"mem_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"jalr_pc_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+16,0,"wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"rs1_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+18,0,"rs2_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+19,0,"rd_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+20,0,"csr_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+21,0,"mem_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"mem_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+23,0,"mem_wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+96,0,"ifu_raddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+97,0,"ifu_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"lsu_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+22,0,"lsu_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+114,0,"lsu_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"lsu_wmask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"lsu_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("dpi_gprs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+32+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("gpr", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+119,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+120,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+105,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+107,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+113,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+19,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+16,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"raddr1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+18,0,"raddr2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+1,0,"rdata1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"rdata2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("dpi_x", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+32+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+20,0,"csr_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+14,0,"csrrw_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+117,0,"csr_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+16,0,"reg_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("rf", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+64+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+98,0,"mcycle",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+99,0,"mcycleh",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+100,0,"mvendorid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+101,0,"marchid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+102,0,"mcycle_total",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_exu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+1,0,"rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"pc_reg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+3,0,"mem_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+117,0,"csr_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"mem_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"is_add",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"is_addi",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"is_lui",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"is_lw",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"is_lbu",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"is_sw",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"is_sb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"is_jalr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"is_auipc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"is_csrrw",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+113,0,"wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+114,0,"mem_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"jalr_pc_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+115,0,"wdata_add",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+24,0,"wdata_addi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"wdata_lui",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+26,0,"wdata_lw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+27,0,"wdata_lbu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+104,0,"wdata_jalr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+28,0,"wdata_auipc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"wdata_csrrw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"mem_wdata_sw",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+116,0,"mem_wdata_sb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+30,0,"lbu_byte",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_idu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+107,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+106,0,"inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+16,0,"wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"rs1_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+18,0,"rs2_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+19,0,"rd_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+20,0,"csr_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+2,0,"imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+5,0,"is_add",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"is_addi",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"is_lui",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"is_lw",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"is_lbu",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"is_sw",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"is_sb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"is_jalr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"is_auipc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"is_csrrw",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"mem_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"mem_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"mem_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"mem_wmask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+110,0,"is_ebreak",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"illegal_instruction",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_ifu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+96,0,"pc_reg",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"ifu_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+97,0,"ifu_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_lsu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+22,0,"mem_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"mem_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+114,0,"mem_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"mem_wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"mem_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+4,0,"lsu_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+22,0,"lsu_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+114,0,"lsu_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"lsu_wmask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"lsu_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_mem", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+105,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"ifu_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+97,0,"ifu_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+21,0,"lsu_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"lsu_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+22,0,"lsu_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+114,0,"lsu_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"lsu_wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"lsu_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_wbu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+105,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+107,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"is_jalr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"jalr_pc_out",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"pc_reg",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+31,0,"pc_dnpc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+117,(0U),32);
    bufp->fullBit(oldp+118,(vlSelfRef.top__DOT__inst_valid));
    bufp->fullIData(oldp+119,(5U),32);
    bufp->fullIData(oldp+120,(0x20U),32);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelfRef.top__DOT__rs1_data),32);
    bufp->fullIData(oldp+2,(vlSelfRef.top__DOT__imm),32);
    bufp->fullIData(oldp+3,(vlSelfRef.top__DOT__lsu_rdata),32);
    bufp->fullIData(oldp+4,(vlSelfRef.top__DOT__mem_addr),32);
    bufp->fullBit(oldp+5,(vlSelfRef.top__DOT__is_add));
    bufp->fullBit(oldp+6,(vlSelfRef.top__DOT__is_addi));
    bufp->fullBit(oldp+7,(vlSelfRef.top__DOT__is_lui));
    bufp->fullBit(oldp+8,(vlSelfRef.top__DOT__is_lw));
    bufp->fullBit(oldp+9,(vlSelfRef.top__DOT__is_lbu));
    bufp->fullBit(oldp+10,(vlSelfRef.top__DOT__is_sw));
    bufp->fullBit(oldp+11,(vlSelfRef.top__DOT__is_sb));
    bufp->fullBit(oldp+12,(vlSelfRef.top__DOT__is_jalr));
    bufp->fullBit(oldp+13,(vlSelfRef.top__DOT__is_auipc));
    bufp->fullBit(oldp+14,(vlSelfRef.top__DOT__is_csrrw));
    bufp->fullIData(oldp+15,(((IData)(vlSelfRef.top__DOT__is_jalr)
                               ? (0xfffffffeU & vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0)
                               : 0U)),32);
    bufp->fullBit(oldp+16,(vlSelfRef.top__DOT__wen));
    bufp->fullCData(oldp+17,(vlSelfRef.top__DOT__rs1_addr),5);
    bufp->fullCData(oldp+18,(vlSelfRef.top__DOT__rs2_addr),5);
    bufp->fullCData(oldp+19,(vlSelfRef.top__DOT__rd_addr),5);
    bufp->fullCData(oldp+20,(vlSelfRef.top__DOT__csr_addr),5);
    bufp->fullBit(oldp+21,(vlSelfRef.top__DOT__mem_valid));
    bufp->fullBit(oldp+22,(vlSelfRef.top__DOT__mem_wen));
    bufp->fullCData(oldp+23,(vlSelfRef.top__DOT__mem_wmask),4);
    bufp->fullIData(oldp+24,(((IData)(vlSelfRef.top__DOT__is_addi)
                               ? vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0
                               : 0U)),32);
    bufp->fullIData(oldp+25,(((IData)(vlSelfRef.top__DOT__is_lui)
                               ? vlSelfRef.top__DOT__imm
                               : 0U)),32);
    bufp->fullIData(oldp+26,(((IData)(vlSelfRef.top__DOT__is_lw)
                               ? vlSelfRef.top__DOT__lsu_rdata
                               : 0U)),32);
    bufp->fullIData(oldp+27,(((IData)(vlSelfRef.top__DOT__is_lbu)
                               ? (0xffU & ((2U & vlSelfRef.top__DOT__mem_addr)
                                            ? ((1U 
                                                & vlSelfRef.top__DOT__mem_addr)
                                                ? (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 0x18U)
                                                : (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 0x10U))
                                            : ((1U 
                                                & vlSelfRef.top__DOT__mem_addr)
                                                ? (vlSelfRef.top__DOT__lsu_rdata 
                                                   >> 8U)
                                                : vlSelfRef.top__DOT__lsu_rdata)))
                               : 0U)),32);
    bufp->fullIData(oldp+28,((vlSelfRef.top__DOT__imm 
                              + vlSelfRef.top__DOT__pc_reg)),32);
    bufp->fullIData(oldp+29,(((IData)(vlSelfRef.top__DOT__is_csrrw)
                               ? vlSelfRef.top__DOT__rs1_data
                               : 0U)),32);
    bufp->fullCData(oldp+30,((0xffU & ((2U & vlSelfRef.top__DOT__mem_addr)
                                        ? ((1U & vlSelfRef.top__DOT__mem_addr)
                                            ? (vlSelfRef.top__DOT__lsu_rdata 
                                               >> 0x18U)
                                            : (vlSelfRef.top__DOT__lsu_rdata 
                                               >> 0x10U))
                                        : ((1U & vlSelfRef.top__DOT__mem_addr)
                                            ? (vlSelfRef.top__DOT__lsu_rdata 
                                               >> 8U)
                                            : vlSelfRef.top__DOT__lsu_rdata)))),8);
    bufp->fullIData(oldp+31,(((IData)(vlSelfRef.top__DOT__is_jalr)
                               ? ((IData)(vlSelfRef.top__DOT__is_jalr)
                                   ? (0xfffffffeU & vlSelfRef.top__DOT__u_exu__DOT____VdfgRegularize_hef1bfb3f_0_0)
                                   : 0U) : ((IData)(4U) 
                                            + vlSelfRef.top__DOT__pc_reg))),32);
    bufp->fullIData(oldp+32,(vlSelfRef.top__DOT__dpi_gprs[0]),32);
    bufp->fullIData(oldp+33,(vlSelfRef.top__DOT__dpi_gprs[1]),32);
    bufp->fullIData(oldp+34,(vlSelfRef.top__DOT__dpi_gprs[2]),32);
    bufp->fullIData(oldp+35,(vlSelfRef.top__DOT__dpi_gprs[3]),32);
    bufp->fullIData(oldp+36,(vlSelfRef.top__DOT__dpi_gprs[4]),32);
    bufp->fullIData(oldp+37,(vlSelfRef.top__DOT__dpi_gprs[5]),32);
    bufp->fullIData(oldp+38,(vlSelfRef.top__DOT__dpi_gprs[6]),32);
    bufp->fullIData(oldp+39,(vlSelfRef.top__DOT__dpi_gprs[7]),32);
    bufp->fullIData(oldp+40,(vlSelfRef.top__DOT__dpi_gprs[8]),32);
    bufp->fullIData(oldp+41,(vlSelfRef.top__DOT__dpi_gprs[9]),32);
    bufp->fullIData(oldp+42,(vlSelfRef.top__DOT__dpi_gprs[10]),32);
    bufp->fullIData(oldp+43,(vlSelfRef.top__DOT__dpi_gprs[11]),32);
    bufp->fullIData(oldp+44,(vlSelfRef.top__DOT__dpi_gprs[12]),32);
    bufp->fullIData(oldp+45,(vlSelfRef.top__DOT__dpi_gprs[13]),32);
    bufp->fullIData(oldp+46,(vlSelfRef.top__DOT__dpi_gprs[14]),32);
    bufp->fullIData(oldp+47,(vlSelfRef.top__DOT__dpi_gprs[15]),32);
    bufp->fullIData(oldp+48,(vlSelfRef.top__DOT__dpi_gprs[16]),32);
    bufp->fullIData(oldp+49,(vlSelfRef.top__DOT__dpi_gprs[17]),32);
    bufp->fullIData(oldp+50,(vlSelfRef.top__DOT__dpi_gprs[18]),32);
    bufp->fullIData(oldp+51,(vlSelfRef.top__DOT__dpi_gprs[19]),32);
    bufp->fullIData(oldp+52,(vlSelfRef.top__DOT__dpi_gprs[20]),32);
    bufp->fullIData(oldp+53,(vlSelfRef.top__DOT__dpi_gprs[21]),32);
    bufp->fullIData(oldp+54,(vlSelfRef.top__DOT__dpi_gprs[22]),32);
    bufp->fullIData(oldp+55,(vlSelfRef.top__DOT__dpi_gprs[23]),32);
    bufp->fullIData(oldp+56,(vlSelfRef.top__DOT__dpi_gprs[24]),32);
    bufp->fullIData(oldp+57,(vlSelfRef.top__DOT__dpi_gprs[25]),32);
    bufp->fullIData(oldp+58,(vlSelfRef.top__DOT__dpi_gprs[26]),32);
    bufp->fullIData(oldp+59,(vlSelfRef.top__DOT__dpi_gprs[27]),32);
    bufp->fullIData(oldp+60,(vlSelfRef.top__DOT__dpi_gprs[28]),32);
    bufp->fullIData(oldp+61,(vlSelfRef.top__DOT__dpi_gprs[29]),32);
    bufp->fullIData(oldp+62,(vlSelfRef.top__DOT__dpi_gprs[30]),32);
    bufp->fullIData(oldp+63,(vlSelfRef.top__DOT__dpi_gprs[31]),32);
    bufp->fullIData(oldp+64,(vlSelfRef.top__DOT__gpr__DOT__rf[0]),32);
    bufp->fullIData(oldp+65,(vlSelfRef.top__DOT__gpr__DOT__rf[1]),32);
    bufp->fullIData(oldp+66,(vlSelfRef.top__DOT__gpr__DOT__rf[2]),32);
    bufp->fullIData(oldp+67,(vlSelfRef.top__DOT__gpr__DOT__rf[3]),32);
    bufp->fullIData(oldp+68,(vlSelfRef.top__DOT__gpr__DOT__rf[4]),32);
    bufp->fullIData(oldp+69,(vlSelfRef.top__DOT__gpr__DOT__rf[5]),32);
    bufp->fullIData(oldp+70,(vlSelfRef.top__DOT__gpr__DOT__rf[6]),32);
    bufp->fullIData(oldp+71,(vlSelfRef.top__DOT__gpr__DOT__rf[7]),32);
    bufp->fullIData(oldp+72,(vlSelfRef.top__DOT__gpr__DOT__rf[8]),32);
    bufp->fullIData(oldp+73,(vlSelfRef.top__DOT__gpr__DOT__rf[9]),32);
    bufp->fullIData(oldp+74,(vlSelfRef.top__DOT__gpr__DOT__rf[10]),32);
    bufp->fullIData(oldp+75,(vlSelfRef.top__DOT__gpr__DOT__rf[11]),32);
    bufp->fullIData(oldp+76,(vlSelfRef.top__DOT__gpr__DOT__rf[12]),32);
    bufp->fullIData(oldp+77,(vlSelfRef.top__DOT__gpr__DOT__rf[13]),32);
    bufp->fullIData(oldp+78,(vlSelfRef.top__DOT__gpr__DOT__rf[14]),32);
    bufp->fullIData(oldp+79,(vlSelfRef.top__DOT__gpr__DOT__rf[15]),32);
    bufp->fullIData(oldp+80,(vlSelfRef.top__DOT__gpr__DOT__rf[16]),32);
    bufp->fullIData(oldp+81,(vlSelfRef.top__DOT__gpr__DOT__rf[17]),32);
    bufp->fullIData(oldp+82,(vlSelfRef.top__DOT__gpr__DOT__rf[18]),32);
    bufp->fullIData(oldp+83,(vlSelfRef.top__DOT__gpr__DOT__rf[19]),32);
    bufp->fullIData(oldp+84,(vlSelfRef.top__DOT__gpr__DOT__rf[20]),32);
    bufp->fullIData(oldp+85,(vlSelfRef.top__DOT__gpr__DOT__rf[21]),32);
    bufp->fullIData(oldp+86,(vlSelfRef.top__DOT__gpr__DOT__rf[22]),32);
    bufp->fullIData(oldp+87,(vlSelfRef.top__DOT__gpr__DOT__rf[23]),32);
    bufp->fullIData(oldp+88,(vlSelfRef.top__DOT__gpr__DOT__rf[24]),32);
    bufp->fullIData(oldp+89,(vlSelfRef.top__DOT__gpr__DOT__rf[25]),32);
    bufp->fullIData(oldp+90,(vlSelfRef.top__DOT__gpr__DOT__rf[26]),32);
    bufp->fullIData(oldp+91,(vlSelfRef.top__DOT__gpr__DOT__rf[27]),32);
    bufp->fullIData(oldp+92,(vlSelfRef.top__DOT__gpr__DOT__rf[28]),32);
    bufp->fullIData(oldp+93,(vlSelfRef.top__DOT__gpr__DOT__rf[29]),32);
    bufp->fullIData(oldp+94,(vlSelfRef.top__DOT__gpr__DOT__rf[30]),32);
    bufp->fullIData(oldp+95,(vlSelfRef.top__DOT__gpr__DOT__rf[31]),32);
    bufp->fullIData(oldp+96,(vlSelfRef.top__DOT__pc_reg),32);
    bufp->fullIData(oldp+97,(vlSelfRef.top__DOT__ifu_rdata),32);
    bufp->fullIData(oldp+98,(vlSelfRef.top__DOT__gpr__DOT__mcycle),32);
    bufp->fullIData(oldp+99,(vlSelfRef.top__DOT__gpr__DOT__mcycleh),32);
    bufp->fullIData(oldp+100,(vlSelfRef.top__DOT__gpr__DOT__mvendorid),32);
    bufp->fullIData(oldp+101,(vlSelfRef.top__DOT__gpr__DOT__marchid),32);
    bufp->fullQData(oldp+102,(vlSelfRef.top__DOT__gpr__DOT__mcycle_total),64);
    bufp->fullIData(oldp+104,(((IData)(4U) + vlSelfRef.top__DOT__pc_reg)),32);
    bufp->fullBit(oldp+105,(vlSelfRef.clk));
    bufp->fullIData(oldp+106,(vlSelfRef.inst),32);
    bufp->fullBit(oldp+107,(vlSelfRef.rst));
    bufp->fullIData(oldp+108,(vlSelfRef.pc),32);
    bufp->fullIData(oldp+109,(vlSelfRef.a0),32);
    bufp->fullBit(oldp+110,(vlSelfRef.is_ebreak));
    bufp->fullBit(oldp+111,(vlSelfRef.illegal_instruction));
    bufp->fullIData(oldp+112,(((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                               [vlSelfRef.top__DOT__rs2_addr])),32);
    bufp->fullIData(oldp+113,(((IData)(vlSelfRef.top__DOT__is_add)
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
    bufp->fullIData(oldp+114,(((IData)(vlSelfRef.top__DOT__is_sw)
                                ? ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                    ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                   [vlSelfRef.top__DOT__rs2_addr])
                                : ((IData)(vlSelfRef.top__DOT__is_sb)
                                    ? ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                        ? 0U : (0xffU 
                                                & vlSelfRef.top__DOT__gpr__DOT__rf
                                                [vlSelfRef.top__DOT__rs2_addr]))
                                    : 0U))),32);
    bufp->fullIData(oldp+115,(((IData)(vlSelfRef.top__DOT__is_add)
                                ? (vlSelfRef.top__DOT__rs1_data 
                                   + ((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                       ? 0U : vlSelfRef.top__DOT__gpr__DOT__rf
                                      [vlSelfRef.top__DOT__rs2_addr]))
                                : 0U)),32);
    bufp->fullIData(oldp+116,(((0U == (IData)(vlSelfRef.top__DOT__rs2_addr))
                                ? 0U : (0xffU & vlSelfRef.top__DOT__gpr__DOT__rf
                                        [vlSelfRef.top__DOT__rs2_addr]))),32);
}
