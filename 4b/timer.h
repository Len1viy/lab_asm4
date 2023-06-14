#ifndef TIMER_H
#define TIMER_H
#include "splay_tree.h"
#include "time.h"

static char *file_read(FILE *file);
int Tree_From_File(SplayTree *tree);
void n_open(SplayTree *tree, FILE *file, int read_cnt);
void D_timing();

#endif

