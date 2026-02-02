#include <svdpi.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
//#include <time.h> 
#include <sys/time.h>
#include "common.h"

#define UART_ADDR    0x10000000 //这里设定为0x10000000，有修改要记得修改trm的putch
#define TIMER_ADDR   0xa0000048

extern const uint32_t MEM_SIZE;
int pmem_read(int raddr) {
    int in_addr = raddr & ~0x3u;
    //printf("[DEBUG] pmem_read: raddr=0x%08x\n", raddr);

    //time
    // if (in_addr >= TIMER_ADDR && in_addr <=0xa0001048) {
    //     struct timespec tv;
    //     // 优先使用CLOCK_MONOTONIC_RAW（更高精度，不受系统时间调整影响）
    //     if (clock_gettime(CLOCK_MONOTONIC_RAW, &tv) != 0) {
    //         // 若出错，降级使用CLOCK_MONOTONIC（保证基础功能）
    //         clock_gettime(CLOCK_MONOTONIC, &tv);
    //     }
    //     // 计算总微秒数：秒→微秒 + 纳秒→微秒（tv_nsec/1000）
    //     unsigned long long total_us = (unsigned long long)tv.tv_sec * 1000000ULL + (tv.tv_nsec / 1000ULL);
    //     printf("[DEBUG] Timer read: %llu us\n", total_us);
    //     return (int)(total_us & 0xFFFFFFFF);  // 返回低32位（支持最大~4294秒，满足测试需求）
    // }


    // 时钟
    if (in_addr == TIMER_ADDR || in_addr == TIMER_ADDR + 4) {
        struct timeval tv;
        if(gettimeofday(&tv,NULL)!=0){
            perror("gettimeofday failed");
            return 0;
        }
        uint64_t nowtime = (uint64_t)tv.tv_sec *1000000ULL + tv.tv_usec;
        if (in_addr == TIMER_ADDR) {
            //printf("1:%lu\n",nowtime & 0xFFFFFFFF);
            return (uint32_t)(nowtime & 0xFFFFFFFF);  // 低32位
        } else {
            //printf("2:%lu\n",nowtime >> 32);
            return (uint32_t)(nowtime >> 32);         // 高32位
        }
    }


    // 串口状态
    if (in_addr == UART_ADDR) {
        return 0x00000001;  // TX ready
    }

    //内存读取
    int idx = ((in_addr-PMEM_BASE) / 4);
    // int idx = (raddr/ 4);
    if (idx >= 0 && idx < MEM_SIZE) {
        return pmem[idx];
    } else {
        return 0;
    }
}

void pmem_write(int waddr, int wdata, my_byte wmask){
    int in_addr = waddr & ~0x3u;
    // printf("waddr: %08x\n",waddr);



    //mmio地址不作修改
    if (in_addr>=UART_ADDR && in_addr <=0x20000000){
        // 串口输出
        if (in_addr == UART_ADDR) {
            if (wmask & 0x1) {
                putchar(wdata & 0xff);
                fflush(stdout);
            }
            if (wmask & 0x2) {
                putchar((wdata >> 8) & 0xff);
                fflush(stdout);
            }
            if (wmask & 0x4) {
                putchar((wdata >> 16) & 0xff);
                fflush(stdout);
            }
            if (wmask & 0x8) {
                putchar((wdata >> 24) & 0xff);
                fflush(stdout);
            }
            return;
        }
    }

    else {
        //正常内存0x80000000对标0
        int idx = ((waddr-PMEM_BASE) / 4);
        //sw
        if (wmask == 0xF){
            pmem[idx] = (uint32_t)wdata;
            return;
        }


        //sb 
        else{
            pmem[idx] = (wmask == 0x1) ? ((pmem[idx] & 0xFFFFFF00) | (uint32_t)(wdata & 0xFF)) :
                        (wmask == 0x2) ? ((pmem[idx] & 0xFFFF00FF) | ((uint32_t)(wdata & 0xFF) << 8)) :
                        // sh指令，也许之后会用,可能不全，记得补充
                        //(wmask == 0x3) ? ((pmem[idx] & 0xFFFF0000) | (wdata & 0XFF)) :
                        (wmask == 0x4) ? ((pmem[idx] & 0xFF00FFFF) | ((uint32_t)(wdata & 0xFF) << 16)) :
                        (wmask == 0x8) ? ((pmem[idx] & 0x00FFFFFF) | ((uint32_t)(wdata & 0xFF) << 24)) :
                        pmem[idx];
            
            return;
        }
    }
}


void print_halt(int pc_value){
    printf("\n===== Halt Triggered! =====\n");
    printf("Breakpoint at PC: 0x%08x\n", pc_value);
    printf("Simulation paused by ebreak.\n");
    printf("=============================\n");
}
