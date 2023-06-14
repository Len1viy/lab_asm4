#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiv.h"

#define MAX_SIZE 2

int main() {
    Table table = {NULL, MAX_SIZE, 0};
    table.ks = realloc(table.ks, sizeof(KeySpace)*table.msize);
    for (int i = 0; i < table.msize; i++) {
        table.ks[i].key = NULL;
    }
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Del, D_Show, D_Find_versions, D_Perehash};
    while (rc = check_command()) {
        if (!fptr[rc](&table)) break;
    }
    D_Del_table(&table);

}
