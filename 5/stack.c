#include "stack.h"


Element *create_element(int key) {
    Element *elem = calloc(1, sizeof(Element));
    elem->key = key;
    elem->next = NULL;
}

Stack *create_stack() {
    Stack *stack = calloc(1, sizeof(Stack));
    stack->head = NULL;
    return stack;
}

int delete_element(Element *elem) {
    if (elem->next) {
        delete_element(elem->next);
    }
    free(elem);
}

int delete_stack(Stack *stack) {
    delete_element(stack->head);
    free(stack);
}

int stack_add(Element *elem, Stack *stack) {
    if (!stack->head) {
        stack->head = elem;
    } else {
        elem->next = stack->head;
        stack->head = elem;
    }
}
