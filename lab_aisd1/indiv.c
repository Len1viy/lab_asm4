#include <stdio.h>
#include <stdlib.h>
#include "indiv.h"


int is_palind(int n) {
    if (n < 0) {
        n = (-1) * n;
    }
    int nn = n;
    int cnt = 0;
    while (nn > 0) {
        cnt += 1;
        nn /= 10;
    }
    int ost = 0;
    int *array = malloc(sizeof(int) * cnt);
    int i = 0;
    while (n > 0) {
        ost = n % 10;
        array[i] = ost;
        i++;
        n /= 10;
    }
    int flag = 0;
    for (int j = 0; j < cnt / 2 + 1; j++) {
        if (array[j] != array[cnt - j - 1]) {
            flag = 1;
            break;
        }
    }
    free(array);
    return flag;
}

Matrix indiv(Matrix *matr) {
    Matrix ans = {0, NULL};
    ans.lines = matr->lines;
    ans.arr_of_r = malloc(ans.lines * sizeof(struct Line));
    for (int i = 0; i < matr->lines; i++) {
        int ind_ans_c = 0;
        ans.arr_of_r[i].arr_of_l = malloc(sizeof(int) * matr->arr_of_r[i].n);
        for (int j = 0; j < matr->arr_of_r[i].n; j++) {
            if (is_palind(matr->arr_of_r[i].arr_of_l[j]) == 0) {
                ans.arr_of_r[i].arr_of_l[ind_ans_c] = matr->arr_of_r[i].arr_of_l[j];
                ind_ans_c++;
            }
        }
        ans.arr_of_r[i].arr_of_l = realloc(ans.arr_of_r[i].arr_of_l, sizeof(int)*ind_ans_c);
        ans.arr_of_r[i].n = ind_ans_c;
        printf("\n");
    }
    return ans;
}
