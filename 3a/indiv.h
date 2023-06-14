#ifndef INDIV_H
#define INDIV_H

#include "types.h"

int myln(const char *st);
void summator(char *res, char *sm, size_t n);
char *in_str();

void help();

int check_command();

int insert(Table *ptab, unsigned int k, unsigned park, char *info);
int D_Find_key(Table *ptab, unsigned int key);
int D_Find_par(Table *ptab, unsigned int key);
int D_Add(Table *ptab);
int D_Show(Table *ptab);
int D_Del_table(Table *ptab);
int D_Find(Table *ptab);
int D_Find_By_Parents(Table *ptab);
int D_Del(Table *ptab);


#endif
