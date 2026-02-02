#include <svdpi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include "common.h"

#define UART_ADDR       0x10000000
#define TIMER_ADDR      0xa0000048
#define PMEM_BASE       0x80000000

extern const uint32_t MEM_SIZE;
extern std::vector<uint32_t> pmem;

int pmem_read(int raddr) {
    uint32_t addr = (uint32_t)raddr;              // 强制无符号，防止负数
    uint32_t word_addr = addr & ~0x3u;

    // 1. 处理定时器 (64位，分成低32 + 高32)
    if (word_addr == TIMER_ADDR) {
        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0) {
            perror("gettimeofday failed");
            return 0;
        }
        uint64_t us = (uint64_t)tv.tv_sec * 1000000ULL + tv.tv_usec;
        return (uint32_t)(us & 0xFFFFFFFFULL);     // 低32位
    }
    if (word_addr == (TIMER_ADDR + 4)) {
        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0) {
            return 0;
        }
        uint64_t us = (uint64_t)tv.tv_sec * 1000000ULL + tv.tv_usec;
        return (uint32_t)(us >> 32);               // 高32位
    }

    // 2. 串口状态寄存器（简单返回 TX ready）
    if (word_addr == UART_ADDR) {
        return 0x00000001;  // 表示可以发送
    }

    // 3. 正常内存范围
    if (addr >= PMEM_BASE && addr < (PMEM_BASE + (MEM_SIZE << 2))) {
        uint32_t idx = (addr - PMEM_BASE) >> 2;
        return (int)pmem[idx];
    }

    // 非法地址：可打印警告（调试用），生产可注释
    // fprintf(stderr, "[WARN] read invalid addr 0x%08x\n", addr);
    return 0;
}

void pmem_write(int waddr, int wdata, my_byte wmask) {
    uint32_t addr = (uint32_t)waddr;
    uint32_t word_addr = addr & ~0x3u;

    // 1. 串口写（putchar）
    if (word_addr == UART_ADDR) {
        if (wmask & 0x1) putchar( wdata        & 0xff);
        if (wmask & 0x2) putchar((wdata >>  8) & 0xff);
        if (wmask & 0x4) putchar((wdata >> 16) & 0xff);
        if (wmask & 0x8) putchar((wdata >> 24) & 0xff);
        fflush(stdout);
        return;
    }

    // 2. 正常内存写
    if (addr >= PMEM_BASE && addr < (PMEM_BASE + (MEM_SIZE << 2))) {
        uint32_t idx = (addr - PMEM_BASE) >> 2;

        if (wmask == 0xf) {
            // sw 全字写
            pmem[idx] = (uint32_t)wdata;
        } else {
            // sb / sh 部分写（按字节合并）
            uint32_t old = pmem[idx];
            if (wmask & 0x1) old = (old & 0xffffff00) | ( wdata        & 0xff);
            if (wmask & 0x2) old = (old & 0xffff00ff) | ((wdata >>  8) & 0xff) <<  8;
            if (wmask & 0x4) old = (old & 0xff00ffff) | ((wdata >> 16) & 0xff) << 16;
            if (wmask & 0x8) old = (old & 0x00ffffff) | ((wdata >> 24) & 0xff) << 24;
            pmem[idx] = old;
        }
        return;
    }

    // 非法写：可打印警告
    // fprintf(stderr, "[WARN] write invalid addr 0x%08x mask=0x%02x\n", addr, wmask);
}

void print_halt(int pc_value) {
    printf("\n===== Halt Triggered! =====\n");
    printf("  Breakpoint at PC: 0x%08x\n", pc_value);
    printf("  Simulation stopped by ebreak.\n");
    printf("=============================\n");
}