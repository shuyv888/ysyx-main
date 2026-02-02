// utils.cpp
#include "utils.h"
#include "common.h"
#include <verilated.h>
#ifdef ENABLE_WAVE
#include <verilated_vcd_c.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

void load_program(const std::string& path) {
    // 判断是 .bin 还是 .hex（简单后缀判断）
    size_t dot_pos = path.find_last_of('.');
    std::string ext = (dot_pos != std::string::npos) ? path.substr(dot_pos) : "";

    if (ext == ".bin" || ext.empty()) {  // 默认当 bin 处理
        FILE* fp = fopen(path.c_str(), "rb");
        if (!fp) {
            fprintf(stderr, "ERROR: 无法打开 BIN 文件 %s\n", path.c_str());
            exit(1);
        }
        uint8_t* buf = reinterpret_cast<uint8_t*>(pmem_rom.data());
        size_t bytes_read = fread(buf, 1, MEM_SIZE * 4, fp);
        fclose(fp);
        printf("从 %s 加载 BIN 完成：%zu 字节\n", path.c_str(), bytes_read);
    } else if (ext == ".hex") {
        std::ifstream file(path);
        if (!file.is_open()) {
            fprintf(stderr, "错误: 无法打开 HEX 文件 %s\n", path.c_str());
            exit(1);
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#' || line.find(':') == std::string::npos) continue;

            size_t colon = line.find(':');
            std::string addr_str = line.substr(0, colon);
            std::string data_str = line.substr(colon + 1);

            uint32_t word_addr = std::stoul(addr_str, nullptr, 16);

            size_t pos = 0, offset = 0;
            while (pos < data_str.size()) {
                while (pos < data_str.size() && data_str[pos] == ' ') ++pos;
                if (pos + 8 > data_str.size()) break;
                std::string word_str = data_str.substr(pos, 8);
                pos += 8;

                uint32_t inst = std::stoul(word_str, nullptr, 16);
                uint32_t final_addr = word_addr + offset;
                if (final_addr < MEM_SIZE) {
                    pmem_rom[final_addr] = inst;
                }
                ++offset;
            }
        }
        file.close();
        printf("从 %s 加载 HEX 完成\n", path.c_str());
    } else {
        fprintf(stderr, "不支持的文件格式: %s\n", path.c_str());
        exit(1);
    }

    // 拷贝到运行内存
    std::copy(pmem_rom.begin(), pmem_rom.end(), pmem.begin());
}
// utils.cpp


void init_verilator(
    Vtop*& top, 
#ifdef ENABLE_WAVE
    VerilatedVcdC*& tfp, 
#endif
    int argc, char** argv
) {
    Verilated::commandArgs(argc, argv);
#ifdef ENABLE_WAVE
    Verilated::traceEverOn(true);
#endif

    top = new Vtop;

#ifdef ENABLE_WAVE
    tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sim/wave_top.vcd");
#endif

    printf("Verilator 初始化完成\n");
}

void reset_cpu(
    Vtop* top, 
#ifdef ENABLE_WAVE
    VerilatedVcdC* tfp, 
#endif
    vluint64_t& main_time
) {
    // 复位开始
    top->rst = 1;
    top->clk = 0;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(main_time);
#endif
    main_time += 10;

    // 一个上升沿
    top->clk = 1;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(main_time);
#endif
    main_time += 10;

    // 释放复位
    top->rst = 0;
    top->clk = 0;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(main_time);
#endif
    main_time += 10;

    printf("复位完成，开始仿真...\n");
}

bool run_one_cycle(Vtop* top
#ifdef ENABLE_WAVE
    , VerilatedVcdC* tfp
#endif
    , vluint64_t& main_time) {

    top->clk = 0;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(main_time);
#endif
    main_time += 10;

    if (top->is_ebreak) {
        return true;  // 结束信号
    }

    top->clk = 1;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(main_time);
#endif
    main_time += 10;

    return false;
}

void run_simulation(Vtop* top
#ifdef ENABLE_WAVE
    , VerilatedVcdC* tfp
#endif
    , vluint64_t& main_time
    , uint64_t max_cycles) {

    uint64_t cycle = 0;

    while (cycle < max_cycles) {
        if (run_one_cycle(top
#ifdef ENABLE_WAVE
            , tfp
#endif
            , main_time)) {
            printf("检测到 ebreak，仿真结束\n");
            break;
        }
        ++cycle;
    }

    if (cycle >= max_cycles) {
        printf("达到最大周期 %lu，强制退出（可能死循环）\n", max_cycles);
    }
}

void print_simulation_result(Vtop* top, uint64_t cycle) {
    printf("\n仿真结束\n");
    printf("总周期: %lu\n", cycle);
    printf("最终 PC: 0x%08x\n", top->pc);

    if (top->is_ebreak) {
        if (top->a0 == 0) {
            printf("PASS! (a0 == 0)\n");
        } else {
            printf("FAIL! (a0 = 0x%08x)\n", top->a0);
        }
        printf("is_ebreak: %d, a0: 0x%08x\n", top->is_ebreak, top->a0);
    }

    print_halt(top->pc);
}