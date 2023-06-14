#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include "input.h"
#include "stack.h"

typedef struct Graph {
    int countVertexes;
    Vertex *vertexes;
    int **matrix;
} Graph;

Graph *create_graph();

int check_all(int x, int y, int vertex, Graph *graph);

int check_direction(Graph *graph, int from, int to);

int change_matrix(Graph *graph, int cnt);

void add_edge(Graph *graph, int n1, int n2);

int E_Add(Graph *graph);

void add_vertex(Graph *graph, int x, int y, int type);

int V_Add(Graph *graph);

int G_Init(Graph *graph);



int G_Show(Graph *graph);

void del_edges(Graph *graph, int from, int to);

int E_Del(Graph *graph);

int V_Del(Graph *graph);

void delete_graph(Graph *graph);

int change(Graph *graph, int num, int x, int y, int type);

int V_Change(Graph *graph);

void DFS_Visit(Graph *graph, int i, int **colors, int **previouses);

void print_prev(int i, int *prev, int cnt, int **array, int *iter);

int DFS(Graph *graph);


int Floyd(Graph *graph);



int Graph_From_File(Graph *graph);

int Print_Labyrinth(Graph *graph);


int dyicstra(Graph *graph, int entry, int exit);

int Dyicstra(Graph *graph);

#endif
