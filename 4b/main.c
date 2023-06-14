#include "lib_splay_tree/timer.h"

int main() {
    SplayTree *tree = create_tree();
    int rc;
    int (*fptr[])(SplayTree*) = {NULL, E_Add, Tree_Show, Tree_Circumvent, E_Delete, E_Find, Tree_From_File, E_Individual_Find, D_timing, Tree_Graphviz};
    while (rc = check_command()) {
        if (!fptr[rc](tree)) break;
    }
    delete_tree(tree);
    return 0;
}
