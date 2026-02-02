#include "Vtop.h"
#include <verilated.h>       // Verilator仿真头文件（如果用Verilator工具）
// 1. 波形头文件：仅启用波形时包含


#define ENABLE_WAVE


#ifdef ENABLE_WAVE
#include <verilated_vcd_c.h>  // 波形跟踪头文件
#endif
#include <string.h>
#include <sys/stat.h>
//用于文件读取的头文件
#include <fstream>
#include <vector>  // 补充：原代码使用vector，需包含该头文件避免编译错误
#include <cstdint> // 补充：uint32_t/uint64_t依赖
#include <cstdio>  // 补充：fprintf/printf依赖

#include "common.h"

//新pmem初始化
const uint32_t MEM_SIZE = 0x10000000; // 单位：32位字（指令/数据按字存储）

std::vector<uint32_t> pmem(MEM_SIZE, 0);
std::vector<uint32_t> pmem_rom(MEM_SIZE, 0);
std::vector<uint32_t> pmem_mmio(MEM_SIZE, 0);

//加载hex
void load_hex_to_rom(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    fprintf(stderr, "错误: 无法打开HEX文件 %s\n", filename.c_str());
    exit(1);
  }

  std::string line;
  while (std::getline(file, line)) {
    // 跳过空行或注释行
    if (line.empty() || line[0] == '#' || line.find(':') == std::string::npos) {
      continue;
    }

    // 分割地址和数据（例如 "00000: 00000413 00051137 ..."）
    size_t colon_pos = line.find(':');
    std::string addr_str = line.substr(0, colon_pos);  // 地址部分（如"00000"）
    std::string data_str = line.substr(colon_pos + 1); // 数据部分（如"00000413 00051137..."）

    // 转换字地址（十六进制 -> 整数）
    uint32_t word_addr = stoul(addr_str, nullptr, 16);

    // 逐个解析数据部分的指令字（空格分隔）
    uint32_t offset = 0;  // 行内偏移（0,1,2...）
    size_t pos = 0;
    while (pos < data_str.size()) {
      // 跳过空格
      while (pos < data_str.size() && data_str[pos] == ' ') pos++;
      if (pos + 8 > data_str.size()) break;  // 不足8个字符则退出

      // 提取8个字符作为一个指令字（如"00000413"）
      std::string word_str = data_str.substr(pos, 8);
      pos += 8;

      // 转换为32位整数并存储
      uint32_t inst = stoul(word_str, nullptr, 16);
      uint32_t final_addr = word_addr + offset;
      if (final_addr < MEM_SIZE) {  // 检查地址是否越界
        pmem_rom[final_addr] = inst;
      }

      offset++;
    }
  }

  file.close();
  printf("成功：从 %s 加载程序到pmem_rom\n", filename.c_str());
}

void load_bin_to_rom(const char* bin_path) {
    FILE* fp = fopen(bin_path, "rb");
    if (!fp) {
        fprintf(stderr, "ERROR: 无法打开BIN文件 %s\n", bin_path);
        exit(1);
    }
    // 读取BIN文件到pmem_rom（按字节读取，保持原始字节流）
    size_t bytes_read = fread(
        pmem_rom.data(),  // 目标：pmem_rom的字节数组
        1,                // 每次读1字节
        MEM_SIZE,    // 最大读取量
        fp
    );
    fclose(fp);

    printf("BIN加载到pmem_rom完成：读取%ld字节（0x%08x ~ 0x%08lx）\n\n",
           bytes_read, PMEM_BASE, PMEM_BASE + bytes_read - 1);
}

extern "C"{
  
}

int main(int argc, char**argv) {
//打开外部程序到pmem_rom
  if(argv[1] == NULL){
    load_bin_to_rom("/home/shuyv/ysyx-workbench/am-kernels/tests/cpu-tests/build/sum-minirv-npc.bin");
  }
  else{
    load_bin_to_rom(argv[1]);
  }

// 将测试指令复制到 pmem 起始位置（CPU 从 0x80000000 地址取指）
  memcpy(pmem.data(), pmem_rom.data(), pmem_rom.size() * sizeof(uint32_t));

  Verilated::commandArgs(argc, argv);
  // 2. 开启波形跟踪：仅启用波形时执行
#ifdef ENABLE_WAVE
  Verilated::traceEverOn(true);  // 开启波形跟踪
#endif

  Vtop* top = new Vtop;
  // 3. 波形指针定义：仅启用波形时创建
#ifdef ENABLE_WAVE
  VerilatedVcdC* tfp = new VerilatedVcdC;  // 波形文件指针
#endif

  // 4. 初始化波形文件：仅启用波形时执行
#ifdef ENABLE_WAVE
  // 初始化波形文件（确保路径正确）
  top->trace(tfp, 99);
  tfp->open("sim/wave_top.vcd");
#endif

  //因为时间太短看不清楚变化，专门作了个时间变量
  vluint64_t time = 0;  // 时间变量，单位ps

  top->rst = 1;
  top->clk = 0;
  top->eval(); 
  // 5. 波形dump：仅启用波形时执行
#ifdef ENABLE_WAVE
  tfp->dump(time);
#endif
  time +=10;

  top->clk = 1;
  top->eval(); 
#ifdef ENABLE_WAVE
  tfp->dump(time);
#endif
  time += 10;

  top->rst = 0; 
  top->clk = 0;
  top->eval(); 
#ifdef ENABLE_WAVE
  tfp->dump(time);
#endif
  time += 10;

  uint64_t count = 0;
  printf("开始运行\n");
  while(1) {
    top->clk = 0;
    top->eval();
#ifdef ENABLE_WAVE
    tfp->dump(time);
#endif
    time += 10;
    
    // if(count == 2000){
    //   break;
    // }
    // if(count % 40 == 0){
    //   printf("count=%" PRIu64 ": PC=0x%08x, inst=0x%08x\n", count, top->pc, top->inst);
    // }
    if(count == 4000000) break;
    //printf("count=%" PRIu64 ": PC=0x%08x, inst=0x%08x\n", count, top->pc, top->inst);


    if (top->is_ebreak == 1)
    {
      printf("system ebreak\n");
      break;
    }
    // if (top->is_ecall == 1)
    // {
    //   printf("system ecall\n");
    //   break;
    // }
    top->clk = 1;
    top->eval(); 
#ifdef ENABLE_WAVE
    tfp->dump(time);  // 记录上升沿状态
#endif
    time +=10;

    count++;
  }
  
  // 6. 关闭并释放波形资源：仅启用波形时执行
#ifdef ENABLE_WAVE
  //关闭波形文件（确保内容写入磁盘）
  tfp->dump(time);
  tfp->close();
  delete tfp;
#endif

  delete top;

  printf("\ncount = %" PRIu64 "\n",count);
  printf("PC=0x%08x \n",top->pc);
  if(top->is_ebreak == 1 && top->a0 == 0){
    printf("GOOD a0\n");
    printf("is_ebreak: %d, a0: %08x\n",top->is_ebreak,top->a0); 
  // }else  if (top->is_ecall == 1){
  //   printf("This is ecall!\n");
  //   printf("is_ebreak: %d, a0: %08x\n",top->is_ebreak,top->a0);
  }
  else{
    printf("BAD a0\n");
    printf("is_ebreak: %d, a0: %08x\n",top->is_ebreak,top->a0);
  }

  print_halt(top->pc);

  return 0;
}