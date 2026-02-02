/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/paddr.h>

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
static const uint32_t img [] = {
  // 0x00000297,  // auipc t0,0
  // 0x00028823,  // sb  zero,16(t0)
  // 0x0102c503,  // lbu a0,16(t0)
  // 0x00100073,  // ebreak (used as nemu_trap)
  // 0xdeadbeef  // some data

  // 0x80000000 <_start> 开始的指令序列
0x00000413,  // li      s0, 0
0x80009137,  // lui     sp, 0x80009
0x00010113,  // mv      sp, sp       (等价于 addi sp, sp, 0)
0x800000b7,  // lui     ra, 0x80000
0x02008093,  // addi    ra, ra, 32   (ra = 0x80000000 + 32 = 0x80000020)
0x000080e7,  // jalr    ra           (跳转到 ra 指向的地址)

// 0x80000018 <main> 开始的指令序列
0x00000513,  // li      a0, 0
0x00008067,  // ret                (返回)

// 0x80000020 <_trm_init> 开始的指令序列
0xff410113,  // addi    sp, sp, -12  (栈指针减12，分配栈空间)
0x80000537,  // lui     a0, 0x80000
0x05050513,  // addi    a0, a0, 80   (a0 = 0x80000000 + 80 = 0x80000050)
0x00112423,  // sw      ra, 8(sp)    (将 ra 存入栈偏移8的位置)
0x800000b7,  // lui     ra, 0x80000
0x01808093,  // addi    ra, ra, 24   (ra = 0x80000000 + 24 = 0x80000018)
0x000080e7,  // jalr    ra           (跳转到 ra 指向的 main 函数)
0x00050513,  // mv      a0, a0       (等价于 addi a0, a0, 0，无实际操作)
0x00100073,  // ebreak             (调试断点/异常陷阱)
0x80000237,  // lui     tp, 0x80000
0x04420213,  // addi    tp, tp, 68   (tp = 0x80000000 + 68 = 0x80000044)
0x00020067   // jr      tp           (跳转到 tp 指向的地址)
};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = RESET_VECTOR;

  /* The zero register is always 0. */
  cpu.gpr[0] = 0;
}

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
}
