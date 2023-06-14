#include "matrix.h"

int **create_matrix(int n) {
    int **matr = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        matr[i] = calloc(n, sizeof(int));
    }
    return matr;
}

void delete_matrix(int **matr, int n) {
    for (int i = 0; i < n; i++) {
        free(matr[i]);
    }
    free(matr);
}

void modification_weights(int ***start, int ***end, int k, int cnt) {
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            if (k % 2 == 0) {
                (*end)[i][j] = min((*start)[i][j], (*start)[i][k] + (*start)[k][j]);
            }
            else {
                (*start)[i][j] = min((*end)[i][j], (*end)[i][k] + (*end)[k][j]);
            }
        }
    }
}

int **copy_matr(int **matrix, int n) {
    int **ans = create_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                ans[i][j] = matrix[i][j];
            } else if (i == j) {
                ans[i][j] = 0;
            } else {
                ans[i][j] = 10000;
            }
        }
    }
    return ans;
}
