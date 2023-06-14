#ifndef INDIV_H
#define INDIV_H

#include "unistd.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

int myln(const char *st);
void summator(char *res, char *sm, size_t n);
char *in_str();

Table *create_table(int m_size);
void help();

int check_command();
void reading(Table *ptab, int len, char **info);
void reading_ints(Table *ptab, int *f_key, int *f_par_key, int *ln_info, int index);
int insert(Table *ptab, unsigned int k, unsigned park, char *info, int check);
int D_Find_key(Table *ptab, unsigned int key);
int D_Find_par(Table *ptab, unsigned int key);
int D_Add(Table *ptab);
int D_Show(Table *ptab);
int D_Del_table(Table *ptab);
int D_Find(Table *ptab);
int D_Find_By_Parents(Table *ptab);
int D_Del(Table *ptab);


#endif
