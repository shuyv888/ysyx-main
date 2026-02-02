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
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>

__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    // 方向1：DUT（NPC）→ REF（NEMU），将 buf 数据写入 NEMU 物理内存
    // guest_to_host：NEMU 内置函数，将物理地址转为主机虚拟地址
    memcpy(guest_to_host(addr), buf, n);
  } else if (direction == DIFFTEST_TO_DUT) {
    // 方向2：REF（NEMU）→ DUT（NPC），将 NEMU 物理内存数据读入 buf
    memcpy(buf, guest_to_host(addr), n);
  } else {
    panic("DiffTest: invalid memcpy direction!"); // 非法方向直接报错
  }
}

__EXPORT void difftest_regcpy(void *dut, bool direction) {
  assert(0);
}// 核心逻辑：同步 DUT 和 REF 的 CPU 寄存器状态
  // cpu 是 NEMU 全局的 CPU 状态结构体（包含 pc、gpr、csr 等）
  CPU_state *ref = &cpu;  // NEMU 的 cpu 状态

  if (direction == DIFFTEST_TO_REF) {
    // NPC → NEMU：把 NPC 的寄存器状态拷贝到 NEMU
    memcpy(ref, dut, sizeof(CPU_state));
  } else {
    // NEMU → NPC：把 NEMU 的寄存器状态拷贝给 NPC
    memcpy(dut, ref, sizeof(CPU_state));
  } else {
    panic("DiffTest: invalid regcpy direction!");
  }

__EXPORT void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

__EXPORT void difftest_raise_intr(word_t NO) {
  assert(0);
}

__EXPORT void difftest_init(int port) {
  void init_mem();
  init_mem();
  /* Perform ISA dependent initialization. */
  init_isa();
}
