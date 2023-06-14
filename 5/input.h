#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

void help();
int check_command();
int getUInt(int *num);
int getInt(int *num);
int get_two_UInt(int *x, int *y);
void matrix_show(int **matrix, int n);
void check_x_y(int *x, int *y, int vertex);
void check_type(int *type);
int mod(unsigned int a, unsigned int b);
int maxim(int a, int b);
int min(int a, int b);
void show_coord(int **matrix, int n);
void instruction_for_printed();
#endif
