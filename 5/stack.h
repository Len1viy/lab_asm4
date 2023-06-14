
#ifndef STACK_H
#define STACK_H
#include "stdlib.h"

typedef struct Element {
    int key;
    struct Element *next;
} Element;

typedef struct Stack {
    Element *head;
} Stack;

int delete_element(Element *elem);

int delete_stack(Stack *stack);
int stack_add(Element *elem, Stack *stack);

Element *create_element(int key);
Stack *create_stack();

#endif
