#include <stdio.h>
#include <stdlib.h>
#include "ans.h"

#if defined USE_VECTOR
#include "vector.h"
#elif defined USE_LIST
#include "test.h"
#endif


void answer(char *s) {
    Stack *s_rev = stack_new();
    for (int i = 0; i < strlen(s); i++) {
        stack_push(s_rev, s[i]);
    }
    Stack *st_for_op = stack_new();
    Stack *ans = stack_new();
    char ret;
    int flag = 1;
    char pr;
    while (is_empty(s_rev) == 1) {
        stack_pop(s_rev, &ret);
        pr = ret;
        if (65 <= ret && ret <= 90) {
            stack_push(ans, ret);
        }
        else if (ret == ')') {
            stack_push(st_for_op, ret);
        }
        else if (ret == '(') {
            stack_pop(st_for_op, &ret);
            while (ret != ')') {
                stack_push(ans, ret);
                stack_pop(st_for_op, &ret);
            }
        }
        else {
            while (is_empty(st_for_op) == 1 && ((peek(st_for_op) == '*' || peek(st_for_op) == '/') && (ret == '+' || ret == '-'))) {
                stack_pop(st_for_op, &ret);
                stack_push(ans, ret);

            }
            stack_push(st_for_op, pr);
        }
    }
    while (is_empty(st_for_op) == 1) {
        stack_pop(st_for_op, &ret);
        stack_push(ans, ret);
    }
    stack_del(st_for_op);
    stack_del(s_rev);
    stack_print(ans);
    stack_del(ans);
}
