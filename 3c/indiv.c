#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indiv.h"


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

int inp_uint(unsigned int *num) {
    int n;
    do {
        n = scanf("%u", num);
        if (n < 0) {
            return 0;
        }
        if (n == 0) {
            printf("Error input. Try again: \n");
            scanf("%*s");
        }
    } while (n == 0);
    return 1;
}

int inp_int(int *num) {
        int n;
        do {
                n = scanf("%d", num);
                if (n < 0) return 0;
                if (n == 0) {
                        printf("Error input. Try again: \n");
                        scanf("%*s");
                }
        } while (n == 0);
        return 1;
}

int hash_func(char *str, int mx) {
    int len = strlen(str);
    int e = 0;
    //printf("Enter hash-key-->");
    //scanf("%d", &e);
    for (int i = 0; i < len; i++) {
        e += ((str[i] * (i+4)) + ((i + 7) * 19));
    }
    e %= mx;
    printf("%d\n", e);
    return e;
}

void help() {
    printf("0. Quit\n1. Add\n2. Delete\n3. Show\n4. Find versions\n5. Perehash\n");
}

int check_command() {
    int n = 0;
    help();
    printf("Choose a command-->");
    int f = scanf("%d", &n);
    if (f != EOF) {
        while (f != 1 || (n > 5) || (n < 0)) {
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


int insert_w_v_for_perehash(Table *ptab, char *k, int k1, unsigned int info, int rel, int busy) {
        ptab->ks[k1].info.info = info;
        ptab->ks[k1].key = strdup(k);
        ptab->ks[k1].release = rel;
        ptab->ks[k1].busy = busy;
        return 1;
}

int insert_w_v(Table *ptab, char *k, int busy, int rel, unsigned int info) {
        ptab->ks[ptab->csize].info.info = info;
        ptab->ks[ptab->csize].key = strdup(k);
                ptab->ks[ptab->csize].busy = busy;
        ptab->ks[ptab->csize].release = rel;
        ptab->csize += 1;
}

int insert(Table *ptab, char *k, int k1, unsigned int info, int busy) {
    int rel = 0;
    if (k1 == ptab->msize - 1 && ptab->ks[k1].key != NULL) {
        printf("NEED PEREHASH\n");
        return 1;
    }
    if (ptab->ks[k1].key) {
                for (int i = k1; i < ptab->msize; i++) {
                        if (!(ptab->ks[i].key)) {
                                ptab->ks[i].info.info = info;
                                ptab->ks[i].key = strdup(k);
                                ptab->ks[i].busy = busy;
                                ptab->ks[i].release = rel;
                                break;
                        } else {
                                if (strcmp(ptab->ks[i].key, k) == 0) {
                                        rel = ptab->ks[i].release + 1;
                                }
                        }
                }
        } else {
        ptab->ks[k1].info.info = info;
        ptab->ks[k1].key = strdup(k);
        ptab->ks[k1].busy = busy;
        ptab->ks[k1].release = 0;
    }
    ptab->csize++;
    return 1;
}


int D_Perehash(Table *ptab) {
        Table rewrite = {NULL, ptab->msize * 2, 0};
        rewrite.ks = realloc(rewrite.ks, sizeof(KeySpace)*rewrite.msize);
        for (int i = 0; i < rewrite.msize; i++) {
                rewrite.ks[i].key = NULL;
        }
        rewrite.csize = ptab->csize;
        for (int i = 0; i < ptab->msize; i++) {
                if (ptab->ks[i].key != NULL) {
                        int ind = hash_func(ptab->ks[i].key, rewrite.msize);
                        insert(&rewrite, ptab->ks[i].key, ind, ptab->ks[i].info.info, ptab->ks[i].busy);
                }
        }
        ptab->msize = ptab->msize * 2;
        ptab->ks = realloc(ptab->ks, sizeof(KeySpace)*ptab->msize);
        D_Show(&rewrite);
        printf("\n");
        for (int i = ptab->msize / 2; i < ptab->msize; i++) {
                ptab->ks[i].key = NULL;
        }
        for (int i = 0; i < ptab->msize; i++) {
                if (ptab->ks[i].key != NULL) {
                        ptab->ks[i].key = realloc(ptab->ks[i].key, 0);
                        ptab->ks[i].key = NULL;
                }
                        if (rewrite.ks[i].key != NULL) {
                                //printf("rewrite: %d - %d\n", i, rewrite.ks[i].release);
                                insert_w_v_for_perehash(ptab, rewrite.ks[i].key, i, rewrite.ks[i].info.info, rewrite.ks[i].release, rewrite.ks[i].busy);
                                //printf("ptab: %d - %d\n", i, ptab->ks[i].release);
            }
        }
        D_Del_table(&rewrite);
}


int D_Add(Table *ptab) {
    if (ptab->csize == ptab->msize) {
        D_Perehash(ptab);
    }
    unsigned int info;
    printf("Enter key-->");
    scanf("%*c");
    char *k = in_str();
    printf("Enter info-->");
    inp_uint(&info);
    int k1 = hash_func(k, ptab->msize);
    insert(ptab, k, k1, info, 1);
    free(k);
    return 1;
}

int D_Show(Table *ptab) {
    if (ptab->ks) {
        printf("------------------------------------------------------------------\n");
        for (int i = 0; i < ptab->msize; i++) {
                if (ptab->ks[i].key) {
                printf("|\t%d\t|\t%s\t|\t%d\t|\t%u\t|\n", ptab->ks[i].busy, ptab->ks[i].key, ptab->ks[i].release, ptab->ks[i].info.info);
            }
        }
        printf("------------------------------------------------------------------\n");
    } else {
        printf("Table is empty\n");
    }
}


void D_Del_table(Table *ptab) {
    for (int i = 0; i < ptab->msize; i++) {
        if (ptab->ks[i].key) {
                free(ptab->ks[i].key);
        }
    }
    free(ptab->ks);
    ptab->csize = 0;
}








int D_Del(Table *ptab) {

    printf("Enter key which you want delete-->");
    scanf("%*c");
    char *k = in_str();
    int ind = hash_func(k, ptab->msize);
    for (int i = ind; i < ptab->msize; i++)
        if ((ptab->ks[i].key) && (strcmp(ptab->ks[i].key, k) == 0) && (ptab->ks[i].busy == 1)) {
                ptab->ks[i].busy = 0;
                break;
        }
    free(k);
}

int D_Find_versions(Table *ptab) {
    Table vers = {NULL, ptab->msize, 0};
    vers.ks = realloc(vers.ks, sizeof(KeySpace)*vers.msize);
    for (int i = 0; i < vers.msize; i++) {
        vers.ks[i].key = NULL;
    }
    int choose;
    printf("Choose pick: 2 - all versions; 1 - one version");
    scanf("%d", &choose);
    if (choose == 2) {
        printf("Enter key, which you would like to find-->");
        scanf("%*c");
        char *key = in_str();
                int ind = hash_func(key, ptab->msize);
        for (int j = ind; j < ptab->msize; j++) {
                if (ptab->ks[j].key) {
                if (strcmp(ptab->ks[j].key, key) == 0) {
                        insert_w_v(&vers, key, ptab->ks[j].busy, ptab->ks[j].release, ptab->ks[j].info.info);
                }
            }
        }
        D_Show(&vers);
        D_Del_table(&vers);
        free(key);
    } else {
        printf("Enter key, which you would like to find-->");
        scanf("%*c");
        char *key = in_str();
        int ind = hash_func(key, ptab->msize);
        printf("Enter the version-->");
        int version;
        scanf("%d", &version);
        for (int j = ind; j < ptab->msize; j++) {
                if (ptab->ks[j].key) {
                        if (strcmp(ptab->ks[j].key, key) == 0 && ptab->ks[j].release == version) {
                                insert_w_v(&vers, ptab->ks[j].key, ptab->ks[j].busy, ptab->ks[j].release, ptab->ks[j].info.info);
                        }
                }
        }
        D_Show(&vers);
        D_Del_table(&vers);
        free(key);
    }
}
