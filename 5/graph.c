#include "graph.h"
#include "limits.h"

Graph *create_graph() {
    Graph *graph = calloc(1, sizeof(Graph));
    graph->vertexes = NULL;
    graph->countVertexes = 0;
}

int check_all(int x, int y, int vertex, Graph *graph) {
    for (int i = 0; i < vertex; i++) {
        if (x == graph->vertexes[i].x && y == graph->vertexes[i].y) return 1;
    }
    return 0;
}

int check_direction(Graph *graph, int from, int to) {
    if (to >= graph->countVertexes) {
        printf("Error, there is can't be an edge\n");
        return 1;
    }
    if (mod(graph->vertexes[to].x, graph->vertexes[from].x) == 1 &&
        mod(graph->vertexes[to].y, graph->vertexes[from].y) == 0 ||
        mod(graph->vertexes[to].x, graph->vertexes[from].x) == 0 &&
        mod(graph->vertexes[to].y, graph->vertexes[from].y) == 1)
        return 0;
    else {
        printf("Error, there is can't be an edge\n");
        return 1;
    }
}

int change_matrix(Graph *graph, int cnt) {
    if (cnt != 0) delete_matrix(graph->matrix, cnt);
    graph->matrix = create_matrix(graph->countVertexes);
    for (int i = 0; i < graph->countVertexes; i++) {
        for (int j = 0; j < graph->vertexes[i].countEdges; j++) {
            graph->matrix[i][graph->vertexes[i].edges[j]] = 1;
            graph->matrix[graph->vertexes[i].edges[j]][i] = 1;
        }
    }
}

void add_edge(Graph *graph, int n1, int n2) {
    graph->vertexes[n1 - 1].countEdges++;
    graph->vertexes[n2 - 1].countEdges++;
    graph->vertexes[n1 - 1].edges = realloc(graph->vertexes[n1 - 1].edges,
                                            graph->vertexes[n1 - 1].countEdges * sizeof(int));
    graph->vertexes[n2 - 1].edges = realloc(graph->vertexes[n2 - 1].edges,
                                            graph->vertexes[n2 - 1].countEdges * sizeof(int));
    graph->vertexes[n1 - 1].edges[graph->vertexes[n1 - 1].countEdges - 1] = n2 - 1;
    graph->vertexes[n2 - 1].edges[graph->vertexes[n2 - 1].countEdges - 1] = n1 - 1;
}

int E_Add(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty\n");
        return 2;
    }

    int n1, n2;
    do {
        printf("Input which vertexes you want to connect `n1 n2`-->");
        get_two_UInt(&n1, &n2);
    } while (n1 == n2 || n1 > graph->countVertexes || n2 > graph->countVertexes);
    if (check_direction(graph, n1 - 1, n2 - 1) == 1) {
        printf("These vertexes can't be connected\n");
        return 2;
    }
    add_edge(graph, n1, n2);
    graph->matrix[n1 - 1][n2 - 1] = 1;
    graph->matrix[n2 - 1][n1 - 1] = 1;
    return 1;

}

void add_vertex(Graph *graph, int x, int y, int type) {
    graph->countVertexes++;
    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex) * graph->countVertexes);
    graph->vertexes[graph->countVertexes - 1].x = x;
    graph->vertexes[graph->countVertexes - 1].y = y;
    graph->vertexes[graph->countVertexes - 1].type = type;
    graph->vertexes[graph->countVertexes - 1].countEdges = 0;
    graph->vertexes[graph->countVertexes - 1].edges = NULL;
}

int V_Add(Graph *graph) {
    int x, y, type, edges;
    int cnt = graph->countVertexes;
    do {
        check_x_y(&x, &y, graph->countVertexes + 1);
        check_type(&type);
        printf("Input cnt of directions for vertex number %d-->", graph->countVertexes + 1);
        getInt(&edges);
        while (edges > graph->countVertexes) {
            printf("Error with edges. Try again-->");
            getInt(&edges);
        }
    } while (check_all(x, y, graph->countVertexes, graph) == 1);
    add_vertex(graph, x, y, type);
    if (edges > 0) {
        printf("Choose directions:\n");
        int to;
        for (int j = 0; j < edges; j++) {
            do {
                printf("(If u do error, input `-1`) %d direction for %d -->", j + 1, graph->countVertexes);
                getInt(&to);
                if (to == -1) break;
            } while (check_direction(graph, graph->countVertexes - 1, to - 1) == 1);
            if (to != -1) {
                add_edge(graph, to, graph->countVertexes);
            }
        }
    }
    change_matrix(graph, cnt);
    return 1;
}

int G_Init(Graph *graph) {
    int cnt;
    printf("Input edges-->");
    getInt(&cnt);
    graph->countVertexes = cnt;
    graph->vertexes = malloc(cnt * sizeof(Vertex));
    int x, y, type, edges;
    for (int i = 0; i < cnt; i++) {
        do {
            check_x_y(&x, &y, i + 1);
            check_type(&type);
            printf("Input cnt for directions for vertex number %d-->", i + 1);
            getInt(&edges);
            while (edges > graph->countVertexes - 1) {
                printf("Error with edges. Try again-->");
                getInt(&edges);
            }

        } while (check_all(x, y, i, graph) == 1);
        graph->vertexes[i].x = x;
        graph->vertexes[i].y = y;
        graph->vertexes[i].type = type;
        graph->vertexes[i].countEdges = edges;
        graph->vertexes[i].edges = malloc(sizeof(int) * graph->vertexes[i].countEdges);
        if (edges > 0) for (int f = 0; f < edges; f++) graph->vertexes[i].edges[f] = -1;
    }
    printf("Choose directions:\n");
    int to;
    for (int i = 0; i < cnt; i++) {
        printf("Directions for vertex %d\n", i + 1);
        if (graph->vertexes[i].countEdges > 0) {
            for (int j = 0; j < graph->vertexes[i].countEdges; j++) {
                if (graph->vertexes[i].edges[j] == -1) {
                    do {
                        printf("%d direction for %d -->", j + 1, i + 1);
                        getInt(&to);
                    } while (check_direction(graph, i, to - 1) == 1);
                    graph->vertexes[i].edges[j] = to - 1;
                    graph->vertexes[to - 1].edges[j] = i;
                } else continue;
            }
        }
    }
    change_matrix(graph, 0);
    return 1;
}



int G_Show(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty\n");
        return 1;
    }

    for (int i = 0; i < graph->countVertexes; i++) {
        if (graph->vertexes[i].type == 1) {
            printf("Vertex number %d is entry, has location (%d, %d) and direction to", i + 1, graph->vertexes[i].x,
                   graph->vertexes[i].y);
        }
        if (graph->vertexes[i].type == 0) {
            printf("Vertex number %d is default, has location (%d, %d) and direction to", i + 1, graph->vertexes[i].x,
                   graph->vertexes[i].y);
        }
        if (graph->vertexes[i].type == -1) {
            printf("Vertex number %d is exit, has location (%d, %d) and direction to", i + 1, graph->vertexes[i].x,
                   graph->vertexes[i].y);
        }

        for (int j = 0; j < graph->vertexes[i].countEdges; j++) {
            printf(" ");
            printf("%d", graph->vertexes[i].edges[j] + 1);
        }
        printf("\n");
    }
    matrix_show(graph->matrix, graph->countVertexes);
    return 1;
}

void del_edges(Graph *graph, int from, int to) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty.\n");
        return;
    }


    for (int i = 0; i < graph->vertexes[from].countEdges; i++) {
        if (graph->vertexes[from].edges[i] == to) {
            if (graph->vertexes[from].countEdges == 1) {
                graph->vertexes[from].countEdges--;
                graph->vertexes[from].edges = realloc(graph->vertexes[from].edges, 0);
            } else {
                for (int j = i; j < graph->vertexes[from].countEdges - 1; j++) {
                    graph->vertexes[from].edges[j] = graph->vertexes[from].edges[j + 1];
                }
                graph->vertexes[from].countEdges -= 1;
                graph->vertexes[from].edges = realloc(graph->vertexes[from].edges,
                                                      graph->vertexes[from].countEdges * sizeof(int));
                break;
            }
        }
    }

}

int E_Del(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty\n");
        return 2;
    }
    int n1, n2;
    printf("Input which edge you want to delete `n1 n2` -->");
    do {
        get_two_UInt(&n1, &n2);
    } while (n1 > graph->countVertexes || n2 > graph->countVertexes || n1 == n2);
    del_edges(graph, n1 - 1, n2 - 1);
    del_edges(graph, n2 - 1, n1 - 1);
    graph->matrix[n1 - 1][n2 - 1] = 0;
    graph->matrix[n2 - 1][n1 - 1] = 0;

    return 1;
}

int V_Del(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty.\n");
        return 2;
    }
    int num;
    do {
        printf("Input which vertex you want to delete (input `-1` to cansel) -->");
        getInt(&num);
    } while (num > graph->countVertexes);
    if (num == -1) {
        printf("Action was canseled!\n");
        return 2;
    }
    for (int i = 0; i < graph->vertexes[num - 1].countEdges; i++) {
        del_edges(graph, graph->vertexes[num - 1].edges[i], num - 1);
    }
    for (int i = 0; i < graph->countVertexes; i++) {
        for (int j = 0; j < graph->vertexes[i].countEdges; j++) {
            if (graph->vertexes[i].edges[j] > num - 1) {
                graph->vertexes[i].edges[j]--;
            }
        }
    }
    Vertex deliting = graph->vertexes[num - 1];
    free(deliting.edges);
    for (int i = num - 1; i < graph->countVertexes - 1; i++) {
        graph->vertexes[i] = graph->vertexes[i + 1];
    }
    graph->vertexes[graph->countVertexes - 1] = deliting;
    int cnt = graph->countVertexes;
    graph->countVertexes--;
    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex) * graph->countVertexes);
    change_matrix(graph, cnt);

    return 1;
}

void delete_graph(Graph *graph) {
    for (int i = 0; i < graph->countVertexes; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    for (int i = 0; i < graph->countVertexes; i++) {
        free(graph->vertexes[i].edges);
    }
    free(graph->vertexes);
    free(graph);
}

int change(Graph *graph, int num, int x, int y, int type) {
    graph->vertexes[num].x = x;
    graph->vertexes[num].y = y;
    graph->vertexes[num].type = type;
    for (int i = 0; i < graph->vertexes[num].countEdges; i++) {
        del_edges(graph, graph->vertexes[num].edges[i], num);
    }
    graph->vertexes[num].edges = realloc(graph->vertexes[num].edges, 0);
    graph->vertexes[num].countEdges = 0;
    return 1;
}

int V_Change(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty.\n");
        return 2;
    }
    int num;
    do {
        printf("Input which vertex you want to change (input `-1` to cansel) -->");
        getInt(&num);
    } while (num > graph->countVertexes);
    if (num == -1) {
        printf("Action was canseled!\n");
        return 2;
    }
    printf("Input new X, Y, TYPE, for vertex %d\n", num);
    int x, y, type;
    do {
        check_x_y(&x, &y, 0);
        check_type(&type);
    } while (check_all(x, y, graph->countVertexes, graph) == 1);
    change(graph, num - 1, x, y, type);
    for (int i = 0; i < graph->countVertexes; i++) {
        graph->matrix[i][num - 1] = 0;
        graph->matrix[num - 1][i] = 0;
    }
}

void DFS_Visit(Graph *graph, int i, int **colors, int **previouses) {
    (*colors)[i] = 1;
    for (int u = 0; u < graph->vertexes[i].countEdges; u++) {
        int next = graph->vertexes[i].edges[u];
        if ((*colors)[next] == 0) {
            (*previouses)[next] = i;
            DFS_Visit(graph, next, colors, previouses);
        }
    }
    (*colors)[i] = 2;

}

void print_prev(int i, int *prev, int cnt, int **array, int *iter) {
    (*array)[*iter] = i;
    for (int j = 0; j < cnt; j++) {
        if (prev[j] == i) {
            (*iter)++;
            print_prev(j, prev, cnt, array, iter);
        }
    }
    return;
}

int DFS(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty.\n");
        return 2;
    }
    printf("Input the vertex of entry -->");
    int start;
    getInt(&start);
    if (graph->vertexes[start - 1].type != 1) {
        printf("It is not an entry :(\n");
        return 2;
    }
    int *colors = calloc(graph->countVertexes, sizeof(int));
    int *previouses = calloc(graph->countVertexes, sizeof(int));
    for (int i = 0; i < graph->countVertexes; i++) {
        colors[i] = 0;
        previouses[i] = 100;
    }
    if (colors[start - 1] == 0) DFS_Visit(graph, start - 1, &colors, &previouses);
    int *array = calloc(graph->countVertexes, sizeof(int));
    int iter = 0;
    for (int i = 0; i < graph->countVertexes; i++) {
        if (previouses[i] == 100) {
            print_prev(i, previouses, graph->countVertexes, &array, &iter);
            break;
        }
    }
    int flag = 1;
    for (int i = 0; i < iter + 1; i++) {
        if (graph->vertexes[array[i]].type == -1) {
            flag = 0;
            printf("There is an exit from this entrance\n");
            int check = 0;
            while (check <= i) {
                printf("%d ", array[check] + 1);
                check++;
            }
            printf("\n");
            break;
        }
    }
    if (flag == 1) printf("There is no exit from this entrance\n");
    free(colors);
    free(previouses);
    free(array);
}


int Floyd(Graph *graph) {
    if (graph->countVertexes == 0) {
        printf("Graph is empty.\n");
        return 2;
    }
    int **start_weights = copy_matr(graph->matrix, graph->countVertexes);
    int **end_weights = copy_matr(graph->matrix, graph->countVertexes);
    int n;
    do {
        printf("Input the entry (-1 for cansel) -->");
        getInt(&n);
    } while ((n != -1) && (graph->vertexes[n-1].type != 1));
    if (n == -1) return 2;
    for (int i = 0; i < graph->countVertexes; i++) {
        modification_weights(&start_weights, &end_weights, i, graph->countVertexes);
    }
    int closest = 1000;
    int ind = 0;
    for (int i = 0; i < graph->countVertexes; i++) {
        if (start_weights[n-1][i] < closest && graph->vertexes[i].type == -1) {
            closest = start_weights[n-1][i];
            ind = i + 1;
        }
    }
    if (ind == 0) {
        printf("There is no exit\n");
        return 2;
    }
    delete_matrix(start_weights, graph->countVertexes);
    delete_matrix(end_weights, graph->countVertexes);
    printf("The closest exit for this entry is %d. Weight of it %d\n", ind, closest);
    return 1;
}



int Graph_From_File(Graph *graph) {
//    FILE *file = fopen("C:\\Users\\vadim\\CLionProjects\\KR3\\graph.txt", "r");
    FILE *file = fopen("graph.txt", "r");
    int cnt;
    fscanf(file, "%d\n", &cnt);
    graph->countVertexes = cnt;
    graph->vertexes = calloc(cnt, sizeof(Vertex));
    int x, y, type, dirs, vert;
    for (int i = 0; i < cnt; i++) {
        fscanf(file, "%d %d %d %d\n", &x, &y, &type, &dirs);
        graph->vertexes[i].x = x;
        graph->vertexes[i].y = y;
        graph->vertexes[i].type = type;
        graph->vertexes[i].countEdges = dirs;
        graph->vertexes[i].edges = calloc(dirs, sizeof(int));
        for (int j = 0; j < dirs; j++) {
            fscanf(file, "%d ", &vert);
            graph->vertexes[i].edges[j] = vert - 1;
        }
        fscanf(file, "\n");
    }
    graph->matrix = create_matrix(cnt);
    change_matrix(graph, cnt);
    fclose(file);
    return 1;
}

int Print_Labyrinth(Graph *graph) {
    unsigned int max_x = 0;
    unsigned int max_y = 0;
    unsigned int min_x = 1000;
    unsigned int min_y = 1000;
    unsigned int max;
    for (int i = 0; i < graph->countVertexes; i++) {
        if (graph->vertexes[i].x > max_x) max_x = graph->vertexes[i].x;
        if (graph->vertexes[i].y > max_y) max_y = graph->vertexes[i].y;
        if (graph->vertexes[i].x < min_x) min_x = graph->vertexes[i].x;
        if (graph->vertexes[i].x < min_y) min_y = graph->vertexes[i].y;
    }
    if (max_x > max_y) max = max_x;
    else max = max_y;
    int **matrix_for_print = create_matrix((int) (2 * max + 1));
    for (int i = 0; i < graph->countVertexes; i++) {
        matrix_for_print[(max - graph->vertexes[i].y) * 2][graph->vertexes[i].x * 2] = i + 1;
    }
    int max_for_print_y, max_for_print_x;
    for (int i = 0; i < graph->countVertexes; i++) {
        for (int j = 0; j < graph->vertexes[i].countEdges; j++) {
            max_for_print_x = maxim(graph->vertexes[i].x, graph->vertexes[graph->vertexes[i].edges[j]].x) * 2;
            max_for_print_y = maxim(graph->vertexes[i].y, graph->vertexes[graph->vertexes[i].edges[j]].y);
            if (graph->vertexes[graph->vertexes[i].edges[j]].type == 0) {
                if (graph->vertexes[i].type == 1) {
                    if (max_for_print_x == 0 && max_for_print_y != graph->vertexes[i].y)
                        matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -9; // |
                    else if (max_for_print_x == 0 && max_for_print_y == graph->vertexes[i].y)
                        matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -14; // |
                    else if (max_for_print_y == 0 && max_for_print_x / 2 == graph->vertexes[i].x)
                        matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -8; // -<
                    else if (max_for_print_y == 0 && max_for_print_x / 2 != graph->vertexes[i].x)
                        matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -7; // >-
                } else if (graph->vertexes[i].type == -1) {
                    if (max_for_print_x == 0 && max_for_print_y == graph->vertexes[i].y)
                        matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -2; // ^^
                    else if (max_for_print_x == 0 && max_for_print_y != graph->vertexes[i].y)
                        matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -1; // VV
                    else if (max_for_print_y == 0 && max_for_print_x / 2 == graph->vertexes[i].x)
                        matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -4; // =>
                    else if (max_for_print_y == 0 && max_for_print_x / 2 != graph->vertexes[i].x)
                        matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -3; // <=
                } else {
                    if (max_for_print_x == 0)
                        matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -5; // ||
                    else if (max_for_print_y == 0)
                        matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -6; // ==
                }
            } else if (graph->vertexes[graph->vertexes[i].edges[j]].type == -1 && graph->vertexes[i].type == 1) {
                if (max_for_print_x == 0 && max_for_print_y == graph->vertexes[i].y)
                    matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -10; // V|
                else if (max_for_print_x == 0 && max_for_print_y != graph->vertexes[i].y)
                    matrix_for_print[(max - max_for_print_y) * 2 + 1][graph->vertexes[i].x * 2] = -11; // |^
                else if (max_for_print_y == 0 && max_for_print_x / 2 == graph->vertexes[i].x)
                    matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -12; // <<
                else if (max_for_print_y == 0 && max_for_print_x / 2 != graph->vertexes[i].x)
                    matrix_for_print[(max - graph->vertexes[i].y) * 2][max_for_print_x - 1] = -13; // >>
            }


        }
    }
    instruction_for_printed();
    show_coord(matrix_for_print, (int) (2 * max + 1));
    delete_matrix(matrix_for_print, 2 * max + 1);
    return 1;
}


int dyicstra(Graph *graph, int entry, int exit) {
    int **weights = copy_matr(graph->matrix, graph->countVertexes);
    for (int i = 0; i < graph->countVertexes; i++) {
        for (int j = 0; j < graph->countVertexes; j++) {
            if (weights[i][j] == 0) weights[i][j] = 10000;
        }
    }
//    matrix_show(weights, graph->countVertexes);
    int *min_weights = calloc(graph->countVertexes, sizeof(int));
    int *visited = calloc(graph->countVertexes, sizeof(int));
    int *previouses = calloc(graph->countVertexes, sizeof(int));
    for (int i = 0; i < graph->countVertexes; i++) {
        min_weights[i] = weights[entry - 1][i];
        visited[i] = -1;
        previouses[i] = 100;
    }
    min_weights[entry - 1] = 0;
    int ind = 0, u = 0;
    for (int i = 0; i < graph->countVertexes; i++) {
        int min = INT_MAX;
        for (int j = 0; j < graph->countVertexes; j++) {
            if (visited[j] == -1 && min_weights[j] < min) {
                min = min_weights[j];
                ind = j;
            }
        }
        u = ind;
        visited[u] = 1;
        for (int j = 0; j < graph->countVertexes; j++) {
            if (visited[j] == -1 && weights[u][j] != 10000 && min_weights[j] > (min_weights[u] + weights[u][j])) {
                min_weights[j] = min_weights[u] + weights[u][j];
                previouses[j] = u;
            }
        }
    }
    if (min_weights[exit - 1] != 10000) {
        printf("%d -> %d = %d\n", entry, exit, min_weights[exit-1]);
        int end = exit - 1;
        Stack *stack = create_stack();
        Element *elem = create_element(end);
        stack_add(elem, stack);

        while (end != 100) {
            elem = create_element(previouses[end]);
            if (previouses[end] == 100) {
                delete_element(elem);
                break;
            }
            stack_add(elem, stack);
            end = previouses[end];
        }
        stack_add(create_element(entry - 1), stack);
        Element *pr = stack->head;
        while (pr) {
            printf("%d ", pr->key + 1);
            pr = pr->next;
        }
        printf("\n");
        delete_stack(stack);
        free(min_weights);
        delete_matrix(weights, graph->countVertexes);
        free(previouses);
        free(visited);
        return 1;
    }
    else {
        printf("There is no exit from this entry\n");
        free(min_weights);
        delete_matrix(weights, graph->countVertexes);
        free(previouses);
        free(visited);
        return 2;
    }
}

int Dyicstra(Graph *graph) {

    int entry, exit;
    do {
        printf("Input entry and exit as `entry exit` -->");
        get_two_UInt(&entry, &exit);
        if (entry > graph->countVertexes || exit > graph->countVertexes || entry == -1 || exit == -1) {
            printf("Error input\n");
            return 2;
        }
    } while (graph->vertexes[entry - 1].type != 1 || graph->vertexes[exit - 1].type != -1);
    dyicstra(graph, entry, exit);
    return 1;
}
