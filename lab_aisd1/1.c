#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "indiv.h"

int inp_int(int *num) {
    int n;
    do {
        n = scanf("%d", num);
        if (n < 0) {
            return 0;
        }
        if (n == 0) {
            printf("Ошибка, повторите попытку: \n");
            scanf("%*s");
        }
    } while (n == 0);
    return 1;
}

int input_matr(Matrix *matr) {
    int m;
    do {
        printf("Введите кол-во строк:");
        if (inp_int(&m) == 0) {
            return 0;
        }
        if (m < 1) {
            printf("Ошибка, повторите попытку: \n");
        }
    } while (m < 1);
    matr->lines = m;
    matr->arr_of_r = malloc(m * sizeof(struct Line));
    for (int i = 0; i < m; i++) {
        int n;
        do {
            printf("Введите кол-во столбцов для %d строки ->", i+1);
            if (inp_int(&n) == 0) {
                return 0;
            }
            if (n < 1) {
                printf("Ошибка, повторите попытку: \n");
            }
        } while (n<1);
        matr->arr_of_r[i].n = n;
        matr->arr_of_r[i].arr_of_l = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {

            do {
                printf("Введите элемент [%d][%d]", i, j);

                if (inp_int(&(matr->arr_of_r[i].arr_of_l[j])) == 0) {
                    return 0;
                }
                if (n < 1) {
                    printf("Ошибка, повторите попытку: \n");
                }
            } while (n < 1);
        }
    }
    return 1;

}

void erase(Matrix *matr) {
    for (int i = 0; i < matr->lines; i++) {
        free(matr->arr_of_r[i].arr_of_l);
    }
    free(matr->arr_of_r);
    matr->lines = 0;
    matr->arr_of_r = NULL;
}

void show(Matrix *matr) {
    for (int i = 0; i < matr->lines; i++) {
        for (int j = 0; j < matr->arr_of_r[i].n; j++) {
            printf("%d ", matr->arr_of_r[i].arr_of_l[j]);
        }
        printf("\n");
    }
}


int main() {
    Matrix matr = {0, NULL};
    Matrix res;
    if (input_matr(&matr) == 0) {
        return 1;
    }
    printf("Исходная матрица:\n");
    show(&matr);
    res = indiv(&matr);
    printf("Итоговая матрица:\n");
    show(&res);
    erase(&res);
    erase(&matr);
}
