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

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include "../monitor/sdb/watchpoint.h"
#include <memory/paddr.h>

void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
extern void init_wp_pool();
// void check_watchpoints();
/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful whe
 * n you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10

CPU_state cpu = {};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;

void device_update();

#ifdef CONFIG_IRINGBUF
#define IRINGBUF_SIZE 16

typedef struct {
  vaddr_t pc;
  uint32_t inst;
  int ilen;
  char asm_str[64];
} InstInfo;


static InstInfo iringbuf[IRINGBUF_SIZE];
static uint64_t inst_count = 0;

static void iringbuf_push(vaddr_t pc, uint32_t inst, int ilen) {
  int idx = inst_count % IRINGBUF_SIZE;
  
  iringbuf[idx].pc = pc;
  iringbuf[idx].inst = inst;
  iringbuf[idx].ilen = ilen;
  
  disassemble(iringbuf[idx].asm_str, sizeof(iringbuf[idx].asm_str),
              pc, (uint8_t *)&inst, ilen);
  
  inst_count++;
}

static void iringbuf_print() {
  Log("===================================== Last %d Instructions (IRingBuf) =====================================",
      IRINGBUF_SIZE);

  int print_count = (inst_count < IRINGBUF_SIZE) ? inst_count : IRINGBUF_SIZE;
  int start_idx = (inst_count >= IRINGBUF_SIZE) ? (inst_count - IRINGBUF_SIZE) % IRINGBUF_SIZE : 0;
  
  for (int i = 0; i < print_count; i++) {
    int idx = (start_idx + i) % IRINGBUF_SIZE;
    InstInfo *info = &iringbuf[idx];
    uint8_t *inst_bytes = (uint8_t *)&info->inst;
    
    printf("0x%08x: %02x %02x %02x %02x  %s\n",
           info->pc,                    // 指令地址（0x80000030）
           inst_bytes[3], inst_bytes[2], // 机器码（前4个字节，80 00 00 b7，匹配示例）
           inst_bytes[1], inst_bytes[0],
           info->asm_str);               // 反汇编指令（lui     ra, 0x80000，匹配示例）
  }
  
  Log("==========================================================================================================");
}
#endif


static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));
  // 新增
  // 检查监视点
  #ifdef CONFIG_WATCHPOINT
  check_watchpoints();
  #endif

  #ifdef CONFIG_IRINGBUF
  iringbuf_push(_this->pc, _this->isa.inst, _this->snpc - _this->pc);
  #endif
}

static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  isa_exec_once(s);
  cpu.pc = s->dnpc;
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst;
#ifdef CONFIG_ISA_x86
  for (i = 0; i < ilen; i ++) {
#else
  for (i = ilen - 1; i >= 0; i --) {
#endif
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst, ilen);
#endif
}
static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void assert_fail_msg() {
#ifdef CONFIG_IRINGBUF
  iringbuf_print();
#endif

#ifdef CONFIG_MTRACE
  close_mtrace();   // 新增：确保 abort/panic 时文件被关闭
#endif
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
#ifdef CONFIG_MTRACE
  init_mtrace();
#endif
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT: case NEMU_QUIT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;
#ifdef CONFIG_MTRACE
  close_mtrace();
#endif
  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_ABORT:
      Log("nemu: %s at pc = " FMT_WORD,
          ANSI_FMT("ABORT", ANSI_FG_RED), nemu_state.halt_pc);
      // 出错：打印最近指令（调试核心），再打印统计信息
#ifdef CONFIG_IRINGBUF
      iringbuf_print();
#endif
      statistic();
      break;
    
    case NEMU_END: 
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);
      // fall through
    case NEMU_QUIT: 
      statistic();
  }
}