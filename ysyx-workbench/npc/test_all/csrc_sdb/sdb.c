#include <stdio.h>
#include <stdint.h>
#include "common.h"

#define NR_REGS 32

// 全局数组保存最新寄存器状态
extern uint32_t guest_gprs[NR_REGS];
extern uint32_t guest_pc;

// 供 sdb 调用的打印函数
void isa_reg_display() {
  puts("Registers:");
  for (int i = 0; i < NR_REGS; i += 4) {
    for (int j = 0; j < 4; j++) {
      int idx = i + j;
      printf("%s: 0x%08x  ", reg_name(idx), guest_gprs[idx]);
    }
    putchar('\n');
  }
  printf("pc: 0x%08x\n", guest_pc);  // 如果你有传 pc
}


const char* reg_name(int index) {
  static const char* reg_names[32] = {
      "zero(x0)", "ra(x1)",   "sp(x2)",   "gp(x3)",   "tp(x4)",   "t0(x5)",   "t1(x6)",   "t2(x7)",
      "s0/fp(x8)", "s1(x9)",   "a0(x10)",  "a1(x11)",  "a2(x12)",  "a3(x13)",  "a4(x14)",  "a5(x15)",
      "a6(x16)",  "a7(x17)",  "s2(x18)",  "s3(x19)",  "s4(x20)",  "s5(x21)",  "s6(x22)",  "s7(x23)",
      "s8(x24)",  "s9(x25)",  "s10(x26)", "s11(x27)", "t3(x28)",  "t4(x29)",  "t5(x30)",  "t6(x31)"
  };
  if (index >= 0 && index < 32) {
    return reg_names[index];
  } else {
    return "unknown";
  }
}