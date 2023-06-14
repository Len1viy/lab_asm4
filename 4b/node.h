#ifndef NODE_H
#define NODE_H
#include "item.h"

typedef struct Node {
    char *key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    Item *info;
} Node;

Node* create_node(Item *item, char *key);
void delete_node_all(Node *nd);
int delete_node(Node* nd);


#endif
