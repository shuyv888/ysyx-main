// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VTOP__DPI_H_
#define VERILATED_VTOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at test_all/vsrc_mem/top.v:42:34
    extern void dpi_get_gprs(const svLogicVecVal* gprs, const svLogicVecVal* pc_reg);
    // DPI import at test_all/vsrc_mem/RegisterFile.v:133:33
    extern int pmem_read(int raddr);
    // DPI import at test_all/vsrc_mem/RegisterFile.v:134:34
    extern void pmem_write(int waddr, int wdata, char wmask);

#ifdef __cplusplus
}
#endif

#endif  // guard
