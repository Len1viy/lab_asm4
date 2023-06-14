#ifndef TYPES_H
#define TYPES_H

typedef struct Line {
    int n;
    int *arr_of_l;
} Line;

typedef struct Matrix {
    int lines;
    Line *arr_of_r;
} Matrix;

#endif
