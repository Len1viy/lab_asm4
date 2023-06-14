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

void help() {
    printf("0. Quit\n1. Add\n2. Find\n3. Delete\n4. Show\n5. Find by range of parents keys\n");
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

int insert(Table *ptab, unsigned int k, unsigned park, char *info) {
    ptab->ks[ptab->csize].info.info = strdup(info);
    ptab->ks[ptab->csize].key = k;
    ptab->ks[ptab->csize].par = park;
    ptab->csize += 1;
    return 1;
}

int D_Find_key(Table *ptab, unsigned int key) {
    int ret = -2;
    if (key == 0) {
        return 1;
    };
    for (int i = 0; i < ptab->csize; i++) {
        if (ptab->ks[i].key == key) {
            ret = i;
            break;
        }
    }
    return ret+1;
}

int D_Find_par(Table *ptab, unsigned int key) {
    int ret = -1;
    for (int i = 0; i < ptab->csize; i++) {
        if (ptab->ks[i].par == key) {
            ret = 1;
            break;
        }
    }
    return ret;
}

int D_Add(Table *ptab) {
    if (ptab->csize == ptab->msize) {
        printf("Table is full.\n");
        ptab->msize = 2*ptab->msize;
        ptab->ks = realloc(ptab->ks, sizeof(KeySpace) * ptab->msize);
    }
    unsigned int k;
    unsigned int park;
    do {
        printf("Enter key-->");
        scanf("%u", &k);
        scanf("%*c");
    } while (D_Find_key(ptab, k) != -1);
    do {
        printf("Enter parent's key-->");
        scanf("%u", &park);
        scanf("%*c");
    } while (D_Find_key(ptab, park) == -1);

    printf("Enter info-->");
    char *info = in_str();
    if (info == NULL) {
        return 0;
    }
    insert(ptab, k, park, info);
    free(info);
    return 1;
}

int D_Show(Table *ptab) {
    if (ptab->ks) {
        printf("-------------------------------------------------\n");
        for (int i = 0; i < ptab->csize; i++) {
            printf("|\t%u\t|\t%u\t|\t%s\t|\n", ptab->ks[i].key, ptab->ks[i].par, ptab->ks[i].info.info);
        }
        printf("-------------------------------------------------\n");
    } else {
        printf("Table is empty\n");
    }
}

int D_Del_table(Table *ptab) {
    for (int i = 0; i < ptab->csize; i++) {
        free(ptab->ks[i].info.info);
    }
    free(ptab->ks);
    ptab->csize = 0;
}





int D_Find(Table *ptab) {
    Table find = {NULL, 100, 0};
    int ret = -1;
    unsigned int key;
    printf("Enter key, which you want find-->");
    scanf("%u", &key);
    scanf("%*c");
    for (int i = 0; i < ptab->csize; i++) {
        if (ptab->ks[i].key == key) {
            ret = i;
            insert(&find, ptab->ks[i].key, ptab->ks[i].par, ptab->ks[i].info.info);
        }
    }
    if (ret != -1) {
        printf("The following table elements were found:\n");
        D_Show(&find);
    } else {
        printf("Nothing found\n");
    }
    D_Del_table(&find);
}

int D_Find_By_Parents(Table *ptab) {
    if (!(ptab->ks)) {
        printf("Table is empty. Nothing found");
        return 1;
    }
    printf("Enter the range of parents keys-->\n");
    unsigned int min, max;
    scanf("%u %u", &min, &max);
    scanf("%*c");
    printf("%u %u\n", min, max);
    Table find = {NULL, 100, 0};
    find.ks = realloc(find.ks, sizeof(KeySpace)*find.msize);
    int ret = -1;
    for (int i = 0; i < ptab->csize; i++) {
        if (ptab->ks[i].par <= max && ptab->ks[i].par >= min) {
            ret = i;
            insert(&find, ptab->ks[i].key, ptab->ks[i].par, ptab->ks[i].info.info);
        }
    }
    if (ret != -1) {
        printf("The following table elements were found:\n");
        D_Show(&find);
    } else {
        printf("Nothing found\n");
    }
    D_Del_table(&find);
}

int D_Del(Table *ptab) {
    unsigned int k;
    printf("Enter key which you want delete-->");
    scanf("%u", &k);
    scanf("%*c");
    int ind = D_Find_key(ptab, k) - 1;
    int parent = D_Find_par(ptab, k);
    if (parent == -1) {
        if (ind != -1) {
            if (ind == ptab->csize - 1) {
                free(ptab->ks[ind].info.info);
                ptab->csize--;
            } else {
                free(ptab->ks[ind].info.info);
                for (int j = ind; j < ptab->csize - 1; j++) {
                    ptab->ks[j] = ptab->ks[j + 1];
                    ptab->csize--;
                    return 1;
                }
            }
        }
    } else {
        printf("That's key is parent of another. Try again\n");
    }
}
