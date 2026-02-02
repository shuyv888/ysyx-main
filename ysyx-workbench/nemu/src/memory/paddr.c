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

#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <isa.h>

#include <cpu/cpu.h>
#include <stdio.h>

#if   defined(CONFIG_PMEM_MALLOC)
static uint8_t *pmem = NULL;
#else // CONFIG_PMEM_GARRAY
static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};
#endif

uint8_t* guest_to_host(paddr_t paddr) { return pmem + paddr - CONFIG_MBASE; }
paddr_t host_to_guest(uint8_t *haddr) { return haddr - pmem + CONFIG_MBASE; }

static word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

static void pmem_write(paddr_t addr, int len, word_t data) {
  host_write(guest_to_host(addr), len, data);
}

static void out_of_bound(paddr_t addr) {
  panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
      addr, PMEM_LEFT, PMEM_RIGHT, cpu.pc);
}

void init_mem() {
#if   defined(CONFIG_PMEM_MALLOC)
  pmem = malloc(CONFIG_MSIZE);
  assert(pmem);
#endif
  IFDEF(CONFIG_MEM_RANDOM, memset(pmem, rand(), CONFIG_MSIZE));
  Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", PMEM_LEFT, PMEM_RIGHT);
}

#ifdef CONFIG_MTRACE

static FILE *mtrace_fp = NULL;

void init_mtrace(void) {
  if (mtrace_fp) return;

  const char *filename = "/home/shuyv/ysyx-workbench/nemuout/mtrace.txt";
  mtrace_fp = fopen(filename, "w");
  if (!mtrace_fp) {
    perror("Failed to open nemuout/mtrace.txt");
    Log("===== MTRACE fopen FAILED =====");
    return;
  }

  // 使用行缓冲，方便 tail -f 查看实时输出
  setvbuf(mtrace_fp, NULL, _IOLBF, 0);
  Log("mtrace enabled, logging to %s", filename);
}

void close_mtrace(void) {
  if (mtrace_fp) {
    fclose(mtrace_fp);
    mtrace_fp = NULL;
  }
}

void mtrace_log(paddr_t addr, int len, word_t data, bool is_write) {
  if (!mtrace_fp) return;

  bool should_log = true;

#ifdef CONFIG_MTRACE_COND
  // 在这里填写你的条件判断逻辑（可从 menuconfig 启发）
  // 示例1：只记录主存范围（最常用）
  should_log = (addr >= 0x80000000 && addr < 0x88000000);

  // 示例2：只记录字/双字访问
  // should_log = (len == 4 || len == 8);

  // 示例3：只记录设备访问
  // should_log = !in_pmem(addr);

  // 示例4：只在特定 pc 范围记录
  // should_log = (cpu.pc >= 0x80010000 && cpu.pc < 0x80020000);
#endif

  if (!should_log) return;

  fprintf(mtrace_fp, "%-5s addr=0x%08x len=%d data=0x%0*" PRIx64 " pc=0x%08x\n",
          is_write ? "write" : "read",
          addr,
          len,
          len * 2,           // 十六进制位宽 = len * 2
          (uint64_t)data,
          cpu.pc);
}

#else

// 未开启 CONFIG_MTRACE 时提供空实现
#define init_mtrace()   ((void)0)
#define close_mtrace()  ((void)0)
#define mtrace_log(...) ((void)0)

#endif  // CONFIG_MTRACE

word_t paddr_read(paddr_t addr, int len) {
  word_t ret = 0;
  if (likely(in_pmem(addr))) {
    ret = pmem_read(addr,len);
#ifdef CONFIG_MTRACE
      mtrace_log(addr, len, ret, false);
#endif
    return ret;
  }
  IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
  out_of_bound(addr);
  return 0;
}

void paddr_write(paddr_t addr, int len, word_t data) {
  if (likely(in_pmem(addr))) { 
    pmem_write(addr, len, data);
#ifdef CONFIG_MTRACE
    mtrace_log(addr, len, data, true);
#endif    
    return; }
  IFDEF(CONFIG_DEVICE, 
    mmio_write(addr, len, data); 
#ifdef CONFIG_MTRACE
    mtrace_log(addr, len, data, true);
#endif
  return);
  out_of_bound(addr);
}
