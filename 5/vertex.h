#ifndef VERTEX_H
#define VERTEX_H

#include "stdlib.h"

typedef struct Vertex {
    int countEdges;
    unsigned int x;
    unsigned int y;
    int type;
    int *edges;
} Vertex;

#endif
