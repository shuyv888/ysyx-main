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

#include "sdb.h"
#include <string.h>

#define NR_WP 32
#define WP_EXPR_MAX_LEN 512
typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

  word_t old_value;
  char expr[WP_EXPR_MAX_LEN];
  bool enabled;
  // bool initialized;

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

/*
编写WP* new_wp();
void free_wp(WP *wp);
*/


static WP* new_wp() {
  if (free_ == NULL) { 
    printf("can't new_wp it\n");
    // assert(0);
    return NULL;
  }

  WP* ret = free_;
  free_ = free_->next; 
  
  // 初始化新分配的监视点
  
  ret->next = head;
  head = ret;


  return ret;
} 


void free_wp(WP *wp) {
  if (wp == NULL) return;

  WP* h = head;
  if(h == wp) head = wp ->next;
  else {
			while(h && h->next != wp) h = h->next;
			assert(h);
			h->next = wp->next;
  }
  wp->next = free_;
  free_ = wp;
}

//开启监视点
void wp_start(char *args,word_t res) {
  if (args == NULL) {
    printf("Error: Watchpoint expression is NULL!\n");
    return;
  }

  // 2. 新建监视点，检查是否成功
  WP* wp = new_wp();
  if (wp == NULL) {
    printf("Error: Failed to create new watchpoint!\n");
    return;
  }

  // 3. 安全拷贝表达式（替换strcpy，避免越界）
  // 使用strncpy + 手动加\0，确保不溢出expr缓冲区
  strncpy(wp->expr, args, WP_EXPR_MAX_LEN - 1);
  wp->expr[WP_EXPR_MAX_LEN - 1] = '\0';  // 强制终止符，避免乱码

  // 4. 初始化监视点属性
  wp->old_value = res;
  wp->enabled = true;

  printf("Watchpoint %d: %s\n", wp->NO, wp->expr);
}

//删除监视点
void wp_remove(int no) {
  if (no >= NR_WP){
    printf("No no");
    assert(0);
  }
  
  WP* wp = head;
  while (wp != NULL) {
    if (wp->NO == no) {
      printf("Deleted watchpoint %d: %s\n", no, wp->expr);
      free_wp(wp);
      return;
    }
    wp = wp->next;
  }
  printf("Watchpoint %d not found\n", no);
}

//显示监视点
void wp_info(){
  if (head == NULL) {
    printf("No watchpoints\n");
    return;
  }
  else{
    printf("Num\tType\t\tWhat\tData\n");
    printf("---\t----\t\t----\t----\n");
    WP* info = head;
    while (info != NULL) {
      bool success1;
      printf("%d\twatchpoint\t%s\t%d\n", info->NO, info->expr,expr(info->expr,&success1));
      info =info->next;
    }
  }
}





void check_watchpoints() {
  for (WP *wp = head; wp != NULL; wp = wp->next) {
    if (!wp->enabled) continue;
    bool success;
    uint32_t new_value = expr(wp->expr, &success);
    // 如果求值成功且值发生变化
    if (success && new_value != wp->old_value) {
      printf("\nWatchpoint %d change!\n", wp->NO);
      printf("Expr: %s\n", wp->expr);
      printf("Old value: %u (0x%x)\n", wp->old_value, wp->old_value);
      printf("New value: %u (0x%x)\n", new_value, new_value);
      nemu_state.state = NEMU_STOP;

      wp->old_value = new_value;
    }
  }
}
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

