#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}


void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  // 初始化addr为堆的起始地址
  static uintptr_t addr = 0;
  if (addr == 0) {
    addr = (uintptr_t)heap.start;
  }
  
  // 保存当前地址作为分配的起始地址
  uintptr_t old_addr = addr;
  
  // 更新addr到下一个可用位置
  addr += size;
  
  // 简单的边界检查（可选）
  if (addr > (uintptr_t)heap.end) {
    return NULL;  // 内存不足
  }
  
  return (void *)old_addr;
#endif
  return NULL;
}

void free(void *ptr) {
}

#endif
