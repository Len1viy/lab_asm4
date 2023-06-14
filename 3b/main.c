#include "indiv.h"

int main() {
    Table *table = create_table(100);
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Del, D_Show, D_Find_By_Parents};
    while (rc = check_command()) {
        if (!fptr[rc](table)) break;
    }
    D_Del_table(table);
}
