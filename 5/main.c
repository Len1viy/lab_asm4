#include "stdio.h"
#include "lib_for_graph/graph.h"

int main() {
    Graph *graph = create_graph();
    int rc;
    int (*fptr[])(Graph *) = {NULL, G_Init, V_Add, E_Add, G_Show, V_Del, E_Del, V_Change, DFS, Graph_From_File,
                              Print_Labyrinth, Floyd, Dyicstra};
    while (rc = check_command()) {
        if (!fptr[rc](graph)) break;
    }
    delete_graph(graph);
}
