#include <stdio.h>
#include <stdlib.h>
#include "indiv.h"

int main() {
    Table table = {NULL, 100, 0};
    table.ks = realloc(table.ks, sizeof(KeySpace)*table.msize);
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Del, D_Show, D_Find_By_Parents};
    while (rc = check_command()) {
        if (!fptr[rc](&table)) break;
    }
    D_Del_table(&table);
}
