#include "timer.h"


static char *file_read(FILE *file) {
    char *input = malloc(sizeof (char));
    input[0] = '\0';

    char buf[81] = {0};
    int flag = 1, length = 0, buf_len;
    while (flag > 0) {
        flag = fscanf(file, "%80[^\n]", buf);
        if (flag == EOF) {
            free(input);
            return NULL;
        }
        if (!flag)
            fscanf(file, "%*c");
        else {
            buf_len = strlen(buf);
            length += buf_len;
            input = realloc(input, length + 1);
            memcpy(input + length - buf_len, buf, buf_len * sizeof (char));
            input[length] = '\0';
        }
    }
    return input;
}

int Tree_From_File(Tree *tree) {
//    FILE *file = fopen("text.txt", "r");
    FILE *file = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\text.txt", "r");
    char *value = NULL, *key = NULL;
    while (!feof(file)) {
        key = file_read(file);
        value = file_read(file);
        if (key != NULL && value != NULL){
            add_node(tree, key, value, 0);
        }

        if (value != NULL) free(value);
        if (key != NULL) free(key);
    }
    fclose(file);
    Tree_Show(tree);
    return 1;
}

void n_open(Tree *tree, FILE *file, int read_cnt) {
    char *value = NULL, *key = NULL;
    for (int i = 0; i < read_cnt; i++) {
        key = file_read(file);
        value = file_read(file);
        if (key != NULL && value != NULL){
            add_node(tree, key, value, 0);
        }

        if (value != NULL) free(value);
        if (key != NULL) free(key);
    }
}

void D_timing() {
    Tree *tree = create_tree();;
    FILE *file = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\out.txt", "w");
    FILE *timer = fopen("C:\\Users\\vadim\\CLionProjects\\lab_aisd4a\\inp.txt", "r");
    char key[10];
    clock_t start, end;
    int read_cnt = 500001;
    for (int i = 0; i < read_cnt; i += 5000) {
        n_open(tree, timer, 5000);
        printf("percent: %f\n", (float) i / 5000);
        int add = 0, del = 0, trav = 0, find = 0, sfind = 0;
        for (int f = 0; f < 10; f++) {
            for (int j = 0; j < 9; j++) {
                int r = 97 + rand() % 25;
                key[j] = r;
            }
            key[9] = '\0';


            start = clock();
            add_node(tree, key, key, 1);
            end = clock();
            add += end - start;



            start = clock();
            circumvent_print(tree->head, "z");
            end = clock();
            trav += end - start;



            char *result;
            start = clock();
            find_node(tree->head, key, &result);
            end = clock();
            find += end - start;




            start = clock();
            delete_recur(tree->head, key);
            end = clock();
            del += end - start;




            Node *ans;
            int maxim = 1000000;
            start = clock();
            ind_finding(tree->head, key, &ans, &maxim);
            end = clock();
            sfind += end - start;

        }
        fprintf(file, "INSERT %lf\n", (double ) (add / 10) / CLOCKS_PER_SEC);
        printf("OK1\n");
        fprintf(file, "CIRCUMVENT %lf\n", (double ) (trav / 10) / CLOCKS_PER_SEC);
        printf("OK2\n");
        fprintf(file, "FIND %lf\n", (double ) (find / 10) / CLOCKS_PER_SEC);
        printf("OK3\n");
        fprintf(file, "DELETE %lf\n", (double ) (del / 10) / CLOCKS_PER_SEC);
        printf("OK4\n");
        fprintf(file, "INDIVIDUAL_FIND %lf\n", (double ) (sfind / 10) / CLOCKS_PER_SEC);
        printf("OK5\n");

    }
    fclose(file);
    fclose(timer);
    if (tree != NULL) delete_tree(tree);
}
