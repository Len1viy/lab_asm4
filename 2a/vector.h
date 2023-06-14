#ifndef VECTOR_H
#define VECTOR_H

typedef struct Item {
	char info;
} Item;

typedef struct Stack {
	Item *head;
	int cnt;
} Stack;

Stack *stack_new();

void stack_del(Stack *s);

int stack_push(Stack *s, char data);

int stack_pop(Stack *s, char *out);

void stack_print(Stack *s);

int is_empty(Stack *s);

char peek(Stack *s);


#endif
