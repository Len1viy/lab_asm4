#ifndef TYPES_H
#define TYPES_H


typedef struct Item {
    char *info;
} Item;

typedef struct KeySpace {
    unsigned int key;
    unsigned int par;
    Item info;
} KeySpace;

typedef struct Table {
    KeySpace *ks;
    int msize;
    int csize;
} Table;


#endif
