#include "splay_tree.h"

SplayTree* create_tree(){
    SplayTree* tree = calloc(1, sizeof (SplayTree));
    tree->head = NULL;
    return tree;
}

void delete_tree(SplayTree *tree) {
    delete_node_all(tree->head);
    free(tree);
}

void add_node(SplayTree *tree, char *key, unsigned int value) {
    Node *nd = tree->head;
    Node *add = create_node(create_item(value), key);
    if (!(nd)) {
        tree->head = add;
        return;
    } else {
        while (nd) {
            if (strcmp(add->key, nd->key) > 0) {
                if (nd->right == NULL) {
                    nd->right = add;
                    nd->right->parent = nd;
                    return;
                }
                nd = nd->right;
            } else if (strcmp(add->key, nd->key) < 0) {
                if (nd->left == NULL) {
                    nd->left = add;
                    nd->left->parent = nd;
                    return;
                }
                nd = nd->left;
            } else {
                printf("Dublicate key\n");
                return;
            }
        }
    }
}


int E_Add (SplayTree *tree) {
    printf("Input key-->");
    scanf("%*c");
    char *key = in_str();
    printf("Input info-->");
    unsigned int value;
    inp_int(&value);
    add_node(tree, key, value);
    free(key);
    return 1;
}



void my_print(Node* nd, int height, unsigned int size, int isLeft){
    if (nd->right != NULL){
        my_print(nd->right, height + 1, size + strlen(nd->key), 0);
    }

    if (size == 0){
        printf("----%s|\n", nd->key);
    }
    else {

        if (isLeft == 0) {
            for (int i = 0; i < size + height * 4; i++) {
                printf(" ");
            }
            printf("___%s|\n", nd->key);
        } else {
            for (int i = 0; i < size + height * 4; i++){
                printf(" ");
            }
            printf("~~~%s|\n", nd->key);
        }
    }

    if (nd->left != NULL){
        my_print(nd->left, height + 1, size + strlen(nd->key), 1);
    }
}

int Tree_Show(SplayTree *tree) {
    if (tree->head == NULL){
        printf("Tree is Empty\n");
        return 1;
    }

    printf("\nTree: \n\n");
    my_print(tree->head, 0, 0, 0);
    return 1;
}

Node *rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->right = x;
    y->parent = x->parent;
    x->parent = y;
    return y;
}


Node *leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->left = x;
    y->parent = x->parent;
    x->parent = y;
    return y;
}



Node *splay(Node *root, char* key)
{

    if (root == NULL || strcmp(root->key, key) == 0) {
        return root;
    }

    if (strcmp(root->key, key) > 0)
    {

        if (root->left == NULL) return root;

        if (strcmp(root->left->key, key) > 0)
        {

            root->left->left = splay(root->left->left, key);

            root = rightRotate(root);
        }
        else if (strcmp(root->left->key, key) < 0)
        {

            root->left->right = splay(root->left->right, key);

            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }


        return (root->left == NULL)? root: rightRotate(root);
    }
    else
    {

        if (root->right == NULL) return root;

        if (strcmp(root->right->key, key) > 0)
        {

            root->right->left = splay(root->right->left, key);

            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (strcmp(root->right->key, key) < 0)
        {

            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL)? root: leftRotate(root);
    }
}

int E_Find(SplayTree *root)
{
    if (root->head == NULL) {
        printf("Tree is empty\n");
        return 1;
    }
    printf("Input key for finding -->\n");
    scanf("%*c");
    char *key = in_str();
    Node *ans = splay(root->head, key);
    root->head = ans;
    ans->parent = NULL;
    if (strcmp(ans->key, key) == 0) printf("Key: %s; Information: %d\n", ans->key, ans->info->info);
    else printf("KEY DOESN'T EXIST\n");

    free(key);
    return 1;
}

void delete_recur(Node *nd, char *key) {
    if (nd == NULL) {
        printf("Key doesn'n exist\n");
        return;
    }
    if (strcmp(key, nd->key) == 0){
        if (nd->left == NULL && nd->right == NULL){
            if (nd->parent->left == nd){
                nd->parent->left = NULL;
            }
            if (nd->parent->right == nd){
                nd->parent->right = NULL;
            }
            delete_node(nd);
            return;
        }
        if (nd->left == NULL && nd->right != NULL){
            if (nd->parent->left == nd){
                nd->right->parent = nd->parent;
                nd->parent->left = nd->right;

            }
            if (nd->parent->right == nd){
                nd->right->parent = nd->parent;
                nd->parent->right = nd->right;
            }
            delete_node(nd);
            return;
        }
        if (nd->left != NULL && nd->right == NULL){
            if (nd->parent->left == nd){
                nd->left->parent = nd->parent;
                nd->parent->left = nd->left;
            }
            if (nd->parent->right == nd){
                nd->left->parent = nd->parent;
                nd->parent->right = nd->left;
            }
            delete_node(nd);
            return;
        }
        if (nd->left != NULL && nd->right != NULL) {
            Node *min_node = nd->right;
            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            if (min_node->parent == nd) {
                min_node->left = nd->left;
                nd->left->parent = min_node;
            } else {
                if (min_node->right) {
                    min_node->parent->left = min_node->right;
                    min_node->right->parent = min_node->parent;
                } else {
                    min_node->parent->left = NULL;
                }
                min_node->left = nd->left;
                min_node->right = nd->right;
                if (min_node->left) min_node->left->parent = min_node;
                if (min_node->right) min_node->right->parent = min_node;
            }
            min_node->parent = nd->parent;
            if (nd->parent->left == nd) {
                printf("LEFT\n");
                nd->parent->left = min_node;
            }
            else {
                printf("RIGHT\n");
                nd->parent->right = min_node;
            }
            delete_node(nd);

            return;
        }
    }
    if (strcmp(key, nd->key) < 0){
        delete_recur(nd->left, key);
    }
    if (strcmp(key, nd->key) > 0){
        delete_recur(nd->right, key);
    }
}



int E_Delete(SplayTree *tree) {
    if (tree->head == NULL) {
        printf("Tree is empty");
        return 1;
    }
    printf("Input key, which you want to delete-->");
    scanf("%*c");
    char *key = in_str();
    if (strcmp(tree->head->key, key) == 0) {
        if (tree->head->left == NULL && tree->head->right == NULL) {
            delete_node(tree->head);
            tree->head = NULL;
            free(key);
            return 1;
        }
        if (tree->head->left == NULL && tree->head->right != NULL) {
            Node *temp = tree->head->right;
            delete_node(tree->head);
            tree->head = temp;
            free(key);
            return 1;
        }
        if (tree->head->left != NULL && tree->head->right == NULL) {
            Node *temp = tree->head->left;
            delete_node(tree->head);
            tree->head = temp;
            free(key);
            return 1;
        }

        if (tree->head->left != NULL && tree->head->right != NULL) {
            Node *min_node = tree->head->right;

            while (min_node->left != NULL) {
                min_node = min_node->left;
            }
            if (min_node->parent == tree->head) {
                min_node->left = tree->head->left;
                tree->head->left->parent = min_node;
            } else {
                if (min_node->right) {
                    min_node->parent->left = min_node->right;
                    min_node->right->parent = min_node->parent;
                } else {
                    min_node->parent->left = NULL;
                }
                min_node->left = tree->head->left;
                min_node->right = tree->head->right;
                if (min_node->left) min_node->left->parent = min_node;
                if (min_node->right) min_node->right->parent = min_node;
            }
            min_node->parent = NULL;
            delete_node(tree->head);
            tree->head = min_node;
            free(key);
            return 1;
        }
    } else {
        delete_recur(tree->head, key);
        free(key);
        return 1;
    }
}



void circumvent_print(Node* nd, char *lEdge, char *rEdge){

    if (nd->right != NULL){
        circumvent_print(nd->right, lEdge, rEdge);
    }
    if (strcmp(nd->key, lEdge) >= 0 && strcmp(nd->key, rEdge) <= 0) {
        int len = 0;
        int k = nd->info->info;
        printf("|%u", nd->info->info);
        while (k > 0) {
            k /= 10;
            len += 1;
        }

        for (int i = 0; i < 98 - len - strlen(nd->key); i++) {
            if (i == (49 - len)) printf("|");
            else printf(" ");
        }
        printf("%s|\n", nd->key);
    }

    if (nd->left != NULL){
        circumvent_print(nd->left, lEdge, rEdge);
    }
}

int Tree_Circumvent(SplayTree *tree) {
    if (tree->head == NULL){
        printf("Tree is Empty\n");
        return 1;
    }
    printf("Input first edge-->");
    scanf("%*c");
    char *fEdge = in_str();
    printf("\n");
    printf("Input second edge-->");
    char *sEdge = in_str();
    printf("\n");
    int i = 0;
    while (i < 100) {
        if (i == 0 || i == 50 || i == 99) {
            printf("|");
        } else if (i == (101 / 4)) {
            printf("val");
            i += 2;
        } else if (i == (101 / 4) * 3) {
            printf("key");
            i += 2;
        } else printf(" ");
        i++;
    }
    printf("\n");
    for (int i = 0; i < 100; i++) {
        printf("-");
    }
    printf("\n");
    if (strcmp(fEdge, sEdge) > 0) circumvent_print(tree->head, sEdge, fEdge);
    else if (strcmp(fEdge, sEdge) < 0) circumvent_print(tree->head, fEdge, sEdge);
    free(fEdge);
    free(sEdge);
    return 1;
}

void *ind_finding(Node *nd, char *key, Node **ans, int *maxim) {
    if (nd->right != NULL){
        ind_finding(nd->right, key, ans, maxim);
    }
    char *lower;
    if (strlen(key) > strlen(nd->key)) lower = strdup(nd->key);
    else lower = strdup(key);
    int razn = 0;
    for (int elem = 0; elem < strlen(lower); elem++) {
        if (key[elem] > nd->key[elem]) razn += key[elem] - nd->key[elem];
        else razn += nd->key[elem] - key[elem];
    }
    if (razn < (*maxim) && razn != 0) {
        *maxim = razn;
        *ans = nd;
    }
    free(lower);
    if (nd->left != NULL){
        ind_finding(nd->left, key, ans, maxim);
    }
}

int E_Individual_Find(SplayTree *tree) {
    printf("Input key --> ");
    scanf("%*c");
    char *finding = in_str();
    Node *ans;
    int maxim = 1000000;
    ind_finding(tree->head, finding, &ans, &maxim);
    printf("KEY - %s; INFO - %u", ans->key, ans->info->info);
    printf("\n");
    Node *returning = splay(tree->head, ans->key);
    tree->head = returning;
    returning->parent = NULL;
    free(finding);
    return 1;
}


int Graphviz_redact_file(Node *nd, FILE *file) {
    if (nd == NULL) {
        printf("Tree is empty\n");
        return 2;
    }
    fprintf(file, "\t%s [label=\"%s\"];\n", nd->key, nd->key);
    if (nd -> left != NULL) {
        fprintf(file, "\t%s -> %s [color=\"black:purple;0.5\"]\n", nd->key, nd->left->key);
        Graphviz_redact_file(nd->left, file);
    }
    if (nd -> right != NULL) {
        fprintf(file, "\t%s -> %s [color=\"blue:red;0.5\"]\n", nd->key, nd->right->key);
        Graphviz_redact_file(nd->right, file);
    }
}

int Tree_Graphviz(SplayTree *tree) {
    scanf("%*c");
    char *filename = in_str();
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error with open file.\n");
        return 2;
    }
    fprintf(file, "digraph Tree {\n");
    fprintf(file, "\tnode [color=\"gold\"]");
    Graphviz_redact_file(tree->head, file);
    fprintf(file, "}\n");
    fclose(file);
    free(filename);
}
