#include "node.h"

Node* create_node(Item *item, char *key) {
    Node *nd = calloc(1, sizeof(Node));
    nd->key = strdup(key);
    nd->info = item;
    return nd;
}

void delete_node_all(Node *nd) {
    if (nd == NULL) return;
    if (nd->left != NULL) delete_node_all(nd->left);
    if (nd->right != NULL) delete_node_all(nd->right);
    nd->left = NULL;
    nd->right = NULL;
    nd->parent = NULL;
    free(nd->key);
    free(nd->info);
    free(nd);
}

int delete_node(Node* nd){
    nd->left = NULL;
    nd->right = NULL;
    delete_item(nd->info);
    free(nd->key);
    free(nd);
    return 1;
}
