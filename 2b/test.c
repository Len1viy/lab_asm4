#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"


Stack *stack_new() {
        return (Stack *)calloc(1, sizeof(Stack));
}

void stack_del(Stack *stack) {
        Item *ptr = stack->head;
        Item *ptr_prev;
        while (ptr) {
                ptr_prev = ptr;
                ptr = ptr->next;
                free(ptr_prev);
        }
        free(stack);
}

int stack_push(Stack *stack, char data) {
        Item *n = (Item*)malloc(sizeof(Item));
        if (!n) {
                printf("Ошибка");
                return 1;
        }
        n->info = data;
        n->next = stack->head;
        stack->head = n;
        return 0;
}

int stack_pop(Stack *stack, char *out) {
        if (!stack->head) {
                return 1;
        }
        *out = stack->head->info;
        Item *head = stack->head;
        stack->head = head->next;
        free(head);
        return 0;
}

void stack_print(const Stack *stack) {
    Item *ptr = stack->head;
    while (ptr) {
        printf("%c", ptr->info);
        ptr = ptr->next;
    }
    printf("\n");
}

int is_empty(Stack *stack) {
    Item *ptr = stack->head;
    if (!ptr) {
        return 0;
    }
    return 1;
}

char peek(Stack *s) {
	return s->head->info;
}

