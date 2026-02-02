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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

//加一个函数头文件
#include <memory/vaddr.h>

enum {
  TK_NOTYPE = 256, 
  TK_EQ,        //相等
  TK_NE,        //不等
  /* TODO: Add more token types */
  
  

  TK_NEG,       //负号
                //减号
  TK_HEX,       //十六进制数字
  TK_REG,       //寄存器名字
  TK_NUM,       //数字
  TK_DEREF,     //解引用
  TK_AND,       //逻辑与
                //加号
                //乘号
                //'/'
                //'('
                //')'

  
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {" +", TK_NOTYPE},    // spaces
  {"==", TK_EQ},        // equal
  {"!=", TK_NE},        // not equal


  {"-", '-'},           //不转义
  {"0[xX][0-9a-fA-F]+", TK_HEX},
  {"\\$[a-zA-Z_][a-zA-Z0-9_]*", TK_REG},
  {"[0-9]+", TK_NUM},
  {"\\+", '+'},         // plus
  {"\\*", '*'},
  {"&&", TK_AND},       // logical and
  {"/", '/'},           //不转义
  {"\\(", '('},
  {"\\)", ')'},
  





};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;
//这里改token大小
static Token tokens[1024] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  
  if (e == NULL) {
    printf("DEBUG: ERROR - e is NULL!\n");
    return false;
  }
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
        //这个显示表达式识别执行
        //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //SS     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        


        
        switch (rules[i].token_type) {
        //i make
        //添加了负数逻辑
		    case TK_NOTYPE:
			    break;
            case '-':
                if(nr_token == 0 ||
                     tokens[nr_token-1].type == '(' ||
                     tokens[nr_token-1].type == '+' ||
                     tokens[nr_token-1].type == '-' ||
                     tokens[nr_token-1].type == '*' ||
                     tokens[nr_token-1].type == '/' ||
                     tokens[nr_token-1].type == TK_EQ ||
                     tokens[nr_token-1].type == TK_NE ||
                     tokens[nr_token-1].type == TK_AND){
                        tokens[nr_token].type = TK_NEG;
                }
                else{
                    tokens[nr_token].type = '-';
                }
                strncpy(tokens[nr_token].str, substr_start, substr_len);
                tokens[nr_token].str[substr_len] = '\0';


                // //查看类型对不对
                // switch(tokens[nr_token].type) {
                //     case TK_NUM: printf("type: TK_NUM\n"); break;
                //     case TK_NEG: printf("type: TK_NEG\n"); break;
                //     case '+': printf("type: +\n"); break;
                //     case '-': printf("type: -\n"); break;
                //     case '*': printf("type: *\n"); break;
                //     case '/': printf("type: /\n"); break;
                //     case '(': printf("type: (\n"); break;
                //     case ')': printf("type: )\n"); break;
                //     case TK_DEREF: printf("type: TK_DEREF\n"); break;
                //     case TK_HEX: printf("type: TK_HEX\n"); break;
                //     case TK_REG: printf("type: TK_REG\n"); break;
                //     case TK_EQ: printf("type: TK_EQ\n"); break;
                //     case TK_NE: printf("type: TK_NE\n"); break;
                //     case TK_AND: printf("type: TK_AND\n"); break;
                //     default: printf("type: %d\n", tokens[nr_token-1].type); break;
                // }


                nr_token++;

                break;
            case '*':
                if(nr_token == 0 ||
                     tokens[nr_token-1].type == '(' ||
                     tokens[nr_token-1].type == '+' ||
                     tokens[nr_token-1].type == '-' ||
                     tokens[nr_token-1].type == '*' ||
                     tokens[nr_token-1].type == '/' ||
                     tokens[nr_token-1].type == TK_EQ ||
                     tokens[nr_token-1].type == TK_NE ||
                     tokens[nr_token-1].type == TK_AND){
                        tokens[nr_token].type = TK_DEREF;
                }
                else{
                    tokens[nr_token].type = '*';
                }
                strncpy(tokens[nr_token].str, substr_start, substr_len);
                tokens[nr_token].str[substr_len] = '\0';

                // //查看类型对不对
                // switch(tokens[nr_token].type) {
                //     case TK_NUM: printf("type: TK_NUM\n"); break;
                //     case TK_NEG: printf("type: TK_NEG\n"); break;
                //     case '+': printf("type: +\n"); break;
                //     case '-': printf("type: -\n"); break;
                //     case '*': printf("type: *\n"); break;
                //     case '/': printf("type: /\n"); break;
                //     case '(': printf("type: (\n"); break;
                //     case ')': printf("type: )\n"); break;
                //     case TK_DEREF: printf("type: TK_DEREF\n"); break;
                //     case TK_HEX: printf("type: TK_HEX\n"); break;
                //     case TK_REG: printf("type: TK_REG\n"); break;
                //     case TK_EQ: printf("type: TK_EQ\n"); break;
                //     case TK_NE: printf("type: TK_NE\n"); break;
                //     case TK_AND: printf("type: TK_AND\n"); break;
                //     default: printf("type: %d\n", tokens[nr_token-1].type); break;
                // }
                nr_token++;

                break;

        	default: 
        		tokens[nr_token].type = rules[i].token_type;
        		
        		//保存字符串
			    strncpy(tokens[nr_token].str, substr_start, substr_len);
			    tokens[nr_token].str[substr_len] = '\0';
                
                // //查看类型对不对
                // switch(tokens[nr_token].type) {
                //     case TK_NUM: printf("type: TK_NUM\n"); break;
                //     case TK_NEG: printf("type: TK_NEG\n"); break;
                //     case '+': printf("type: +\n"); break;
                //     case '-': printf("type: -\n"); break;
                //     case '*': printf("type: *\n"); break;
                //     case '/': printf("type: /\n"); break;
                //     case '(': printf("type: (\n"); break;
                //     case ')': printf("type: )\n"); break;
                //     case TK_DEREF: printf("type: TK_DEREF\n"); break;
                //     case TK_HEX: printf("type: TK_HEX\n"); break;
                //     case TK_REG: printf("type: TK_REG\n"); break;
                //     case TK_EQ: printf("type: TK_EQ\n"); break;
                //     case TK_NE: printf("type: TK_NE\n"); break;
                //     case TK_AND: printf("type: TK_AND\n"); break;
                //     default: printf("type: %d\n", tokens[nr_token-1].type); break;
                // }
			
          		nr_token++;

        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}


//自编（


static int check_parentheses(int p, int q) {
    if (tokens[p].type == '(' && tokens[q].type == ')'){
        int n = 0;
        int be = 0;//Bad expression
        int nm = 0;//not match
        for (int i = p; i < q; i++) {
            //判断完最后一位是括号就舍去最后一位的判断
            if (tokens[i].type == '(') {
                n++;
            }
            else if (tokens[i].type == ')') {
                n--;
                if (n == 0) {
                    nm = 1;
                }
                else if (n<0){
                    be = 1;
                } 
            }
        }
        
        if (n == 1) {
            if (be == 1){
                return -1;
                // false, bad expression
            }
            if (nm == 1){
                return 0;
                // false, the leftmost '(' and the rightmost ')' are not matched
            }
            return 1;
            //true
        } else {
            printf("Parentheses not fully matched\n");
            return -1;
            // false, bad expression
        }
    }
    else{
        // false, the whole expression is not surrounded by a matched
        // pair of parenthese
        return 0;
    }
}



static int find_main_operator(int p, int q) {
    int parentheses_count = 0;
    int main_op = -1;
    int main_op_2 =-1;
    // 从左往右扫描，按优先级找运算符
    for (int i = p; i <= q; i++) {
        if (tokens[i].type == '(') {
            parentheses_count++;
        } else if (tokens[i].type == ')') {
            parentheses_count--;
        } else if (parentheses_count == 0) {
            // 优先级最低：逻辑与
            if (tokens[i].type == TK_AND) {
                if (main_op == -1 || main_op_2 <4)
                {
                    main_op = i;
                    main_op_2 = 3;
                }
            }
            // 优先级倒数第二：相等性比较
            else if (tokens[i].type == TK_EQ || tokens[i].type == TK_NE) {
                if (main_op == -1 || main_op_2 <3)
                {
                    main_op = i;
                    main_op_2 = 2;
                }
            }
            // 优先级倒数第三：加减法
            else if (tokens[i].type == '+' || tokens[i].type == '-') {
                if (main_op == -1 || main_op_2 <2) {
                    main_op = i;
                    main_op_2 = 1;
                }
                //负数逻辑改到了make_token
            }
            // 优先级最高：乘除法
            else if (tokens[i].type == '*' || tokens[i].type == '/') {
                if (main_op == -1 || main_op_2 <1) {
                    main_op = i;
                    main_op_2 = 0;
                }
                //解引用逻辑改到了make_token
            }
        }
    }
    
    return main_op;
}

static int eval(int p, int q) {
    if (p > q) {
        assert(0);
        return 0;
    }
    else if (p == q) {
        //////需要添加一个取变量值的处理
        if (tokens[p].type == TK_NUM) {
            return atoi(tokens[p].str);
        }
        //十六进制 
        else if (tokens[p].type == TK_HEX) {
            word_t addr = strtoul(tokens[p].str , NULL, 0);
            return addr ;
        }//寄存器名字
        else if (tokens[p].type == TK_REG){
            bool reg_success;
            char* reg_name = tokens[p].str + 1;
            word_t val = isa_reg_str2val(reg_name, &reg_success);

            if (!reg_success) {
                assert(0);
                return 0;
            }
            return val;
        }
        else {
            assert(0);
            return 0;
        }
    }
    // 查括号
    else if (check_parentheses(p, q) == 1) {
        return eval(p + 1, q - 1);
    }
    // 找主运算符
    else {
        int op = find_main_operator(p, q);
        if (op != -1) {
            // 有运算符，正常处理
            int val1 = eval(p, op - 1);
            int val2 = eval(op + 1, q);
            
            switch (tokens[op].type) {
                case '+': return val1 + val2;
                case '-': return val1 - val2;
                case '*': return val1 * val2;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Expression divided by zero");
                        assert(0);
                        return 0;
                    }
                    return val1 / val2;
                case TK_EQ: return val1 == val2;   // 相等比较
                case TK_NE: return val1 != val2;   // 不等比较
                case TK_AND: return val1 && val2;  // 逻辑与
                default: 
                    assert(0);
                    return 0;
            }
        } else {
            // 没有运算符负号表达式
            if (tokens[p].type == TK_NEG) {
                return -eval(p + 1, q);
            } 
            else if(tokens[p].type == TK_DEREF){
                word_t addr = eval(p + 1, q);
                word_t data = vaddr_read(addr, 4);
                return data;
            }
            else {
                assert(0);
                return 0;
            }
        }
    }
}
//自编 ）


word_t expr(char *e, bool *success) {
    if (!make_token(e)) {
        *success = false;
    return 0;
    }
  /* TODO: Insert codes to evaluate the expression. */

    int result = eval(0, nr_token - 1);
    *success = true;
    return result;
}


