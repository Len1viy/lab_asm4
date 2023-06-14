#ifndef TYPES_H
#define TYPES_H
#include "stdio.h"

typedef struct Table {
    FILE *file;
    int *shifts;
    int msize;
    int csize;
} Table;


#endif
