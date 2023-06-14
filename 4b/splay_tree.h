#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include "node.h"

typedef struct SplayTree {
    Node *head;
} SplayTree;

SplayTree* create_tree();
void delete_tree(SplayTree *tree);
void add_node(SplayTree *tree, char *key, unsigned int value);
int E_Add (SplayTree *tree);
void my_print(Node* nd, int height, unsigned int size, int isLeft);
int Tree_Show(SplayTree *tree);
Node *rightRotate(Node *x);
Node *leftRotate(Node *x);
Node *splay(Node *root, char* key);
int E_Find(SplayTree *root);
void delete_recur(Node *nd, char *key);
int E_Delete(SplayTree *tree);
void circumvent_print(Node* nd, char *lEdge, char *rEdge);
int Tree_Circumvent(SplayTree *tree);
void *ind_finding(Node *nd, char *key, Node **ans, int *maxim);
int E_Individual_Find(SplayTree *tree);

int Graphviz_redact_file(Node *nd, FILE *file);
int Tree_Graphviz(SplayTree *tree);

#endif
