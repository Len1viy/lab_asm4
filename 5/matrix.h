#ifndef MATRIX_H
#define MATRIX_H
#include "vertex.h"


int **create_matrix(int n);
void delete_matrix(int **matr, int n);
void modification_weights(int ***start, int ***end, int k, int cnt);
int **copy_matr(int **matrix, int n);


#endif
