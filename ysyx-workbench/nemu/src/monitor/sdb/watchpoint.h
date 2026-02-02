#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include <common.h>

typedef struct watchpoint {
    int NO;
    struct watchpoint *next;
    char expr[128];
    uint32_t old_value;
    bool enabled;
} WP;

// 函数声明
void init_wp_pool(void);
WP* new_wp(void);
extern WP* head;
extern WP* free_;
void free_wp(WP *wp);
void check_watchpoints();
void wp_watch(char *expr,word_t res);
void wp_remove(int no);
void wp_iterate();
#endif