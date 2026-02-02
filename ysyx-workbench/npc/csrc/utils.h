#ifndef __UTILS_H__
#define __UTILS_H__

// 引入必要的头文件依赖
#include <cstdint>
#include <string>
#include <vector>
#include "Vtop.h"

#ifdef ENABLE_WAVE
#include <verilated_vcd_c.h>
#endif

// 全局常量声明
extern const uint32_t MEM_SIZE;

// 全局内存向量声明（外部引用，实际定义在 utils.cpp）
extern std::vector<uint32_t> pmem;
extern std::vector<uint32_t> pmem_rom;
extern std::vector<uint32_t> pmem_mmio;

// C 全局指针声明（供 dpi-c.c 访问）
extern "C" {
    extern uint32_t* pmem_ptr;
}

// 1. 文件加载相关函数声明
void load_hex_to_rom(const std::string& filename);
void load_bin_to_rom(const char* bin_path);
void load_default_or_custom_bin(int argc, char** argv);

// 2. 内存初始化相关函数声明
void copy_rom_to_pmem();
void init_pmem_ptr();

// 3. 仿真环境初始化相关函数声明
Vtop* init_sim_top();
#ifdef ENABLE_WAVE
void init_sim_wave(Vtop* top, VerilatedVcdC*& tfp, const std::string& wave_path = "sim/wave_top.vcd");
#endif
void reset_sim(Vtop* top, vluint64_t& time, VerilatedVcdC* tfp = nullptr);

// 4. 仿真运行相关函数声明
void run_sim_loop(Vtop* top, vluint64_t& time, uint64_t& count, VerilatedVcdC* tfp = nullptr);

// 5. 仿真收尾相关函数声明
void finish_sim(Vtop* top, uint64_t count, VerilatedVcdC* tfp = nullptr);

#endif // __UTILS_H__