#ifndef INDIV_H
#define INDIV_H

#include "types.h"


int myln(const char *st);
void summator(char *res, char *sm, size_t n);


char *in_str();

int inp_uint(unsigned int *num);

int inp_int(int *num);

int hash_func(char *str, int mx);

void help();

int check_command();

int insert_w_v_for_perehash(Table *ptab, char *k, int k1, unsigned int info, int rel, int busy);
int insert_w_v(Table *ptab, char *k, int busy, int rel, unsigned int info);

int insert(Table *ptab, char *k, int k1, unsigned int info, int busy);


int D_Perehash(Table *ptab);


int D_Add(Table *ptab);
int D_Show(Table *ptab);


void D_Del_table(Table *ptab);








int D_Del(Table *ptab);

int D_Find_versions(Table *ptab);

#endif
