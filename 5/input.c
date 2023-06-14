#include "input.h"

void help() {
    printf("0. Quit\n1. Init\n2. Vertex Add\n3. Edge Add\n4. Show\n5. Delete Vertex\n6. Delete Edge\n"
           "7. Change Vertex\n8. Depth-First Search\n9. Graph from file\n10. Print Labyrinth\n"
           "11. The closest exit from entry that you will choose and weight of it\n12. Finding the shortest distance between entry and exit\n");
}

int check_command() {
    int n = 0;
    help();
    printf("Choose a command-->");
    int f = scanf("%d", &n);
    if (f != EOF) {
        while (f != 1 || (n > 13) || (n < 0)) {
            help();
            printf("Wrong input. Try again-->");
            scanf("%*[^\n]");
            if (f != EOF) {
                f = scanf("%d", &n);
            } else return 0;
        }
    } else return 0;
    return n;
}

int getUInt(int *num) {
    int n;
    do {
        n = scanf("%d", num);
        if (n < 0) return 0;
        else if (n == 0) {
            printf("Wrong input. Try again -->");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    } while (n < 1);
    if (*num < 0) *num = -(*num);
    return 1;
}

int getInt(int *num) {
    int n;
    do {
        n = scanf("%d", num);
        if (n < 0) return 0;
        else if (n == 0) {
            printf("Wrong input. Try again -->");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    } while (n < 1);
    return 1;
}

int get_two_UInt(int *x, int *y) {
    int n;
    do {
        n = scanf("%d %d", x, y);
        if (n < 0) return 0;
        else if (n == 0) {
            printf("Wrong input. Try again -->");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    } while (n < 1);
    if (*x < 0) *x = -(*x);
    if (*y < 0) *y = -(*y);
    return 1;
}

void matrix_show(int **matrix, int n) {
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf(" %.2d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%.2d ", i + 1);
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 10000) printf("i ");
            else printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void check_x_y(int *x, int *y, int vertex) {
    if (vertex != 0) printf("Input X and Y for vertex %d-->", vertex);
    else printf("Input X and Y as `x y`-->");
    get_two_UInt(x, y);
}


void check_type(int *type) {
    do {
        printf("Choose a type of vertex (0 - default; 1 - entry; -1 - exit)-->");
        getInt(type);
    } while (*type > 1 || *type < -1);
}


int mod(unsigned int a, unsigned int b) {
    int res = a - b;
    if (res == -1 || res == 1) return 1;
    else if (res == 0) return 0;
    else return -1;
}

int maxim(int a, int b) {
    if (a > b) return a;
    else if (a < b) return b;
    else return 0;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

void show_coord(int **matrix, int n) {
    printf("   ^\n");
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) printf("%.2d |", (n - i - 1) / 2);
        else printf("   |");
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > 0) printf("%.2d", matrix[i][j]);
            else if (matrix[i][j] == 0) printf("  ");
            else if (matrix[i][j] == -1) printf("VV");
            else if (matrix[i][j] == -2) printf("^^");
            else if (matrix[i][j] == -3) printf("<=");
            else if (matrix[i][j] == -4) printf("=>");
            else if (matrix[i][j] == -5) printf("||");
            else if (matrix[i][j] == -6) printf("==");
            else if (matrix[i][j] == -7) printf(">-");
            else if (matrix[i][j] == -8) printf("-<");
            else if (matrix[i][j] == -9) printf("| ");
            else if (matrix[i][j] == -10) printf("|V");
            else if (matrix[i][j] == -11) printf("|^");
            else if (matrix[i][j] == -12) printf("<-");
            else if (matrix[i][j] == -13) printf("->");
            else if (matrix[i][j] == -14) printf(" |");
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < n; i++) {
        printf("--");
    }

    printf(">\n");
    printf("    ");
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) printf("%.2d", i / 2);
        else printf("  ");
    }
    printf("\n");
}

void instruction_for_printed() {
    printf("INSTRUCTION:\n");
    printf("\" |\" - from entry to default (entry from above)\n\"| \" - from entry to default (entry bottom)\n\">-\" - from entry to default (entry from left)\n\"-< - from entry to default (entry from right)\n\"=>\" - from default to exit (exit from right)\n\"<=\" - from default to exit (exit from left)\"\n\"VV\" - from default to exit (exit bottom)\n\"^^\" - from default to exit (top exit)\n\"==\" and \"||\" - from default to default\n\"->\" - from entry to exit (entry from left)\n\"<-\" - from entry to exit (entry from right)\n\"|^\" - from entry to exit (entry bottom)\n\"|V\" - from entry to exit (entry from above)\n");
}
