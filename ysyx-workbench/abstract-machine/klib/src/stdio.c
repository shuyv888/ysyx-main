#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  char buf[1024]; // 临时缓冲区（大小可按需调整）
  va_list ap;

  va_start(ap, fmt);
  int count = vsprintf(buf, fmt, ap); 
  va_end(ap);
  for (int i = 0; i < count; i++) {
      putch(buf[i]);
  }

  return count;

}

int vsprintf(char *out, const char *fmt, va_list ap) {
  if (!out || !fmt) return 0; // 空指针检查
    char *buf = out; // 跟踪当前写入位置
    int count = 0;   // 统计字符总数

    while (*fmt != '\0') {
        if (*fmt != '%') {
            // 普通字符：直接写入缓冲区
            *buf++ = *fmt++;
            count++;
            continue;
        }

        // 处理格式符（%开头）
        fmt++; // 跳过'%'
        switch (*fmt) {
            case 'd': { // 十进制整数
                int num = va_arg(ap, int);
                char tmp[20]; // 临时存储数字字符
                int tmp_idx = 0;
                int is_neg = 0;

                // 处理负数
                if (num < 0) {
                    is_neg = 1;
                    unsigned int n = (unsigned int)-num; // 避免溢出
                    // 逆序存储数字（个位→高位）
                    do {
                        tmp[tmp_idx++] = '0' + (n % 10);
                    } while ((n /= 10) > 0);
                } else {
                    unsigned int n = (unsigned int)num;
                    do {
                        tmp[tmp_idx++] = '0' + (n % 10);
                    } while ((n /= 10) > 0);
                }

                // 输出负号
                if (is_neg) {
                    *buf++ = '-';
                    count++;
                }

                // 逆序输出数字（高位→个位）
                while (tmp_idx > 0) {
                    *buf++ = tmp[--tmp_idx];
                    count++;
                }
                break;
            }

            case 's': { // 字符串
                const char *s = va_arg(ap, const char*);
                while (*s != '\0') {
                    *buf++ = *s++;
                    count++;
                }
                break;
            }

            case '%': { // 转义%
                *buf++ = '%';
                count++;
                break;
            }

            default: { // 不支持的格式符，直接输出%和原字符
                *buf++ = '%';
                *buf++ = *fmt;
                count += 2;
                break;
            }
        }
        fmt++; // 处理下一个字符
    }
    *buf = '\0'; // 字符串结束符
    return count;
}

int sprintf(char *out, const char *fmt, ...) {/////////~
  va_list ap;
  va_start(ap, fmt);       // 初始化可变参数列表
  int count = vsprintf(out, fmt, ap); // 直接调用vsprintf
  va_end(ap);              // 释放可变参数列表
  return count;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
