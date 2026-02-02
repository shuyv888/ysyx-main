#ifndef COMMON_H
#define COMMON_H

#include <stdint.h> 

//初始化pmem头文件
#include <vector>  // 确保包含 vector 头文件
using namespace std;  // 或显式使用 std::vector

// 条件编译：区分 C 和 C++ 编译器
#ifdef __cplusplus  // 如果是 C++ 编译器
extern "C" {        // 告诉 C++ 编译器：内部函数用 C 链接属性
#endif

// 1. 定义 my_byte 类型（8位无符号，与 Verilog 匹配）
typedef unsigned char my_byte;

// 2. 声明全局变量（extern 表示“在其他文件中定义”）
extern const uint32_t MEM_SIZE;



// extern uint32_t pmem[];
extern vector<uint32_t> pmem;  // 声明为 vector
extern vector<uint32_t> pmem_rom;
extern vector<uint32_t> pmem_mmio;
#define PMEM_BASE 0x80000000


// 3. 声明 DPI 函数（统一为 C 链接属性）
void print_halt(int pc_value);
int pmem_read(int raddr);
void pmem_write(int waddr, int wdata, my_byte wmask);

#ifdef __cplusplus  // 闭合 C++ 编译器的 extern "C"
}
#endif

#endif