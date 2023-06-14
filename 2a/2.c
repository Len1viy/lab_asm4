#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ans.h"

#if defined USE_LIST
#include "test.h"
#elif defined USE_VECTOR
#include "vector.h"
#endif

int myln(const char *st) {
    int i = 0;
    while (st[i]) {
        i++;
    }
    return i;
}

void summator(char *res, char *sm, size_t n)
{
    int i = 0;

    if (n == 0) {
        return;
    }
    while (i < n) {
        res[i] = sm[i];
        i++;
    }
}



char *in_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            return NULL;
        } else if (n > 0) {
            int chunck_len = myln(buf);
            int len_all = len + chunck_len;
            res = realloc(res, len_all + 1);
            summator(&res[len], buf, chunck_len);
            len = len_all;
        } else {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
        res[0] = '\0';
    }
    return res;
}

int formul_check(char *s) {
        if (s == NULL) return 2;
        if (strlen(s) <= 2) return 0;
        int flag = 1;
        int prov = 0;
        int count = 0;
        for (int i = 0; i < strlen(s)-1; i++) {
                if (((s[i] <= 90 && s[i] >= 65) && ((s[i+1] == '+' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '-') || s[i+1] == ')')) || (s[i] == '(' && ((s[i+1] <= 90 && s[i+1] >= 65) || s[i+1] == '(') || (s[i] == ')' && (s[i+1] == '+' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '-')))) {
                        flag = 1;
                }
                else if ((s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '-') && ((s[i+1] <= 90 && s[i+1] >= 65) || s[i+1] == '(')) flag = 1;
                else {
                        break;
                }
                if (s[i] == '(') count++;
                else if (s[i] == ')') count--;
        }
        if (s[strlen(s)-1] == ')') count--;
        if (s[strlen(s)-1] == '+' || s[strlen(s)-1] == '-' || s[strlen(s)-1] == '*' || s[strlen(s)-1] == '/' || s[strlen(s)-1] == '(') return 0;
        if (count != 0) return 0;
        return flag;
}

int main() {
        char *argv = NULL;
        do {
                printf("Введите формулу: ");
                printf("\n");
                argv = in_str();
                if (formul_check(argv) == 1) answer(argv);
                else if (formul_check(argv) == 2) printf("Программа завершена\n");
                else printf("НЕВЕРНЫЙ ВВОД\n");
                free(argv);
        } while (argv != NULL);
        free(argv);
        return 1;
}
