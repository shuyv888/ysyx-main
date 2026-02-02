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

#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();


// // // //测试函数
// extern word_t expr(char *e, bool *success);

// static void test_expressions_from_file(const char *filename) {
//     // 1. 打开文件
//     FILE *fp = fopen(filename, "r");
//     if (fp == NULL) {
//         printf("Cannot open file %s\n", filename);
//         return;
//     }
    
//     printf("Testing expressions from %s:\n", filename);
//     printf("==========================================\n");
    
//     char line[1024];  // 用于存储读取的每一行
//     int test_count = 0;   // 测试用例总数
//     int pass_count = 0;   // 通过的测试用例数
    
//     // 2. 逐行读取文件
//     while (fgets(line, sizeof(line), fp) != NULL) {
//         // 3. 移除行末的换行符
//         char *newline = strchr(line, '\n');
//         if (newline) {
//             *newline = '\0';
//         }
        
//         // 4. 跳过空行
//         if (strlen(line) == 0) {
//             continue;
//         }
        
//         printf("Processing line: %s\n", line);
        
//         // 5. 解析格式：期望结果 表达式
//         // 找到第一个空格的位置
//         char *space = strchr(line, ' ');
//         if (space == NULL) {
//             printf("Warning: Invalid format in line: %s\n", line);
//             continue;
//         }
        
//         // 6. 分割字符串
//         *space = '\0';  // 在空格处分割字符串
//         char *expected_str = line;        // 空格前是期望结果
//         char *expression = space + 1;     // 空格后是表达式
//         printf("Expected: '%s', Expression: '%s'\n", expected_str, expression);
        
//         // 7. 转换期望结果为数字
//         int expected = atoi(expected_str);
//         // 8. 调用我们的表达式求值函数
//         bool success = true;
//         printf("%s\n",(char *)expression);
//         word_t result = expr(expression, &success);
//         // 9. 统计和输出结果
//         test_count++;
//         if (success && result == expected) {
//             printf("PASS: %s = %u\n", expression, result);
//             pass_count++;
//         } else {
//             printf("FAIL: %s = %u (expected %u)\n", expression, result, expected);
//         }
//         printf("\n");
//     }
    
//     // 10. 关闭文件
//     fclose(fp);
    
//     // 11. 输出总结
//     printf("==========================================\n");
//     printf("Test Summary:\n");
//     printf("Total tests: %d\n", test_count);
//     printf("Passed: %d\n", pass_count);
//     printf("Failed: %d\n", test_count - pass_count);
//     if (test_count > 0) {
//         printf("Pass rate: %.2f%%\n", (float)pass_count / test_count * 100);
//     }
// }




int main(int argc, char *argv[]) {






  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Start engine. */
  engine_start();


//测试表达式求值

  // test_expressions_from_file("/home/shuyv/ics2024/nemu/tools/gen-expr/input");

	
//））））））


  return is_exit_status_bad();
}
