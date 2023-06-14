#ifndef TYPES_H
#define TYPES_H

typedef struct Item {
    unsigned int info;
} Item;

typedef struct KeySpace {
    int busy;
    char *key;
    int release;
    Item info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
} Table;

#endif
