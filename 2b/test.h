#ifndef TEST_H
#define TEST_H

typedef struct Item {
        char info;
        struct Item *next;
} Item;

typedef struct Stack {
        Item *head;
} Stack;

Stack *stack_new();

void stack_del(Stack *stack);

int stack_push(Stack *stack, char data);

int stack_pop(Stack *stack, char *out);

void stack_print(const Stack *stack);

char peek(Stack *s);

int is_empty(Stack *stack);

#endif
