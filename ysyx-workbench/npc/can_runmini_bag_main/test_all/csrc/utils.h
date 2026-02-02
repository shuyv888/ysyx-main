// utils.h
#ifndef UTILS_H
#define UTILS_H

#include "Vtop.h"
#ifdef ENABLE_WAVE
#include <verilated_vcd_c.h>
#endif

#include <cstdint>
#include <string>

// 全局变量声明（如果需要跨文件访问）
extern std::vector<uint32_t> pmem;
extern std::vector<uint32_t> pmem_rom;
extern const uint32_t MEM_SIZE;

// 函数声明
void load_program(const std::string& path);
void init_verilator(
    Vtop*& top, 
#ifdef ENABLE_WAVE
    VerilatedVcdC*& tfp, 
#endif
    int argc, char** argv
);

void reset_cpu(
    Vtop* top, 
#ifdef ENABLE_WAVE
    VerilatedVcdC* tfp, 
#endif
    vluint64_t& main_time
);


bool run_one_cycle(Vtop* top
#ifdef ENABLE_WAVE
    , VerilatedVcdC* tfp
#endif
    , vluint64_t& main_time);

void run_simulation(Vtop* top
#ifdef ENABLE_WAVE
    , VerilatedVcdC* tfp
#endif
    , vluint64_t& main_time
    , uint64_t max_cycles = 50000000ULL);

void print_simulation_result(Vtop* top, uint64_t cycle);

#endif