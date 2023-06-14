#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define MEMORY 10

Stack *stack_new() {
	Stack *s = calloc(1, sizeof(Stack));
	s->head = realloc(s->head, MEMORY * sizeof(char));
	return s;
}

void stack_del(Stack *s) {
	free(s->head);
	free(s);
}

int stack_push(Stack *s, char data) {
    if (s->cnt >= MEMORY) {
		printf("Максимально выделенная память уже заполнена. Я выделил еще.\n");
		s->cnt++;
		s->head = realloc(s->head, s->cnt * sizeof(char));
		s->head[s->cnt-1].info = data;
    } else {
   		s->cnt++;
    		s->head[s->cnt-1].info = data;
    }
    return 0;
}



int stack_pop(Stack *s, char *out) {
    if ((s->cnt) == 0) {
        return 1;
    }
    *out = s->head[s->cnt-1].info;
    s->cnt--;
    return 0;
}


void stack_print(Stack *s) {
    for (int i = s->cnt-1; i >= 0; i--) {
        printf("%c", (s->head)[i].info);
    }
    printf("\n");
}


int is_empty(Stack *s) {
    if (s->cnt == 0) {
        return 0;
    }
    return 1;
}

char peek(Stack *s) {
	return s->head[s->cnt-1].info;
}
