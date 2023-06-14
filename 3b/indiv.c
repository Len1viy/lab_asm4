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

Table *create_table(int m_size) {
    static int rs = 0;
    Table *table = calloc(1, sizeof(Table));
    char *filename;
    char checker[4] = {72, 97, 104, 97};
    table->msize = m_size;
    table->shifts = (int *) realloc(table->shifts, table->msize * sizeof(int));
    table->csize = 0;

    printf("Input filename --> ");
    filename = in_str();
    int err = 0;
    if (access(filename, F_OK) == 0) {
        table->file = fopen(filename, "rb+");
        fseek(table->file, 0, SEEK_END);
        if (ftell(table->file) >= 4) {
            int s_len = 4;
            char *str = calloc(s_len, sizeof(char));
            fseek(table->file, 0, SEEK_SET);
            fread(str, sizeof(char), s_len, table->file);
            if (strncmp(checker, str, s_len) == 0) {
                int read_cnt, cnt = -1;
                while (cnt != 2) {
                    cnt = (cnt+1) % 3;
                    if (cnt == 0) table->shifts[table->csize] = ftell(table->file);
                    read_cnt = fread(&s_len, sizeof(int), 1, table->file);
                    if (!read_cnt) {
                        if (cnt == 0) err = 0;
                        break;
                    }
                    str = realloc(str, (s_len + 1) * sizeof(char));
                    read_cnt = fread(str, sizeof(char), s_len, table->file);
                    if (read_cnt < s_len) break;
                    if (cnt == 2) {
                        table->csize++;
                        if (table->csize == m_size) {
                            fseek(table->file, 0, SEEK_SET);
                            (fileno(table->file), ftell(table->file));
                        }
                    }
                }
            }
            free(str);
        }
    }
    if (access(filename, F_OK) || err) {
        printf("New file with this name was created!\n");
        table->file = fopen(filename, "wb+");
        fwrite(checker, sizeof(char), 4, table->file);
    }

    rs += 1;
    free(filename);
    return table;
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

void reading(Table *ptab, int len, char **info) {
    *info = realloc(*info, sizeof(char) * len + 1);
    fread(*info, sizeof(char), len, ptab->file);
    (*info)[len] = '\0';
}

void reading_ints(Table *ptab, int *f_key, int *f_par_key, int *ln_info, int index) {
    fseek(ptab->file, ptab->shifts[index], SEEK_SET);
    fread(f_key, sizeof(int), 1, ptab->file);
    fread(f_par_key, sizeof(int), 1, ptab->file);
    fread(ln_info, sizeof(int), 1, ptab->file);
}

int insert(Table *ptab, unsigned int k, unsigned park, char *info, int check) {
    if (!check) {
        if (ptab->csize == ptab->msize) {
            printf("Table is full.\n");
            ptab->msize = 2*ptab->msize;
        }
        if (D_Find_key(ptab, k) != -1) {
            printf("Dublicate key\n");
            return 1;
        }
        if (D_Find_key(ptab, park) == -1 && park != 0) {
            printf("This parent key doesn't exist. It can't be a parent for new key.\n");
            return 1;
        }
    }
    fseek(ptab->file, 4, SEEK_SET);
    if (ptab->csize > 0) {
        fseek(ptab->file, ptab->shifts[ptab->csize], SEEK_SET);
    }
    ptab->csize++;
    if (ptab->csize == 1) {
        ptab->shifts[ptab->csize - 1] = 4;
        ptab->shifts[ptab->csize] = ptab->shifts[ptab->csize - 1] + 12 + strlen(info);
    } else ptab->shifts[ptab->csize] = ptab->shifts[ptab->csize - 1] + 12 + strlen(info);
    int len_info = strlen(info);
    fwrite(&k, sizeof(int), 1, ptab->file);
    fwrite(&park, sizeof(int), 1, ptab->file);
    fwrite(&len_info, sizeof(int), 1, ptab->file);
    fwrite(info, sizeof(char), len_info, ptab->file);
}

int D_Find_key(Table *ptab, unsigned int key) {
    int key_check = 0;
    for (int i = 0; i < ptab->csize; i++) {
        fseek(ptab->file, ptab->shifts[i], SEEK_SET);
        fread(&key_check, sizeof(int), 1, ptab->file);
        if (key_check == key) {
            return i;
        }
    }
    return -1;
}

int D_Find_par(Table *ptab, unsigned int key) {
    int key_check, par_check;
    for (int i = 0; i < ptab->csize; i++) {
        fseek(ptab->file, ptab->shifts[i], SEEK_SET);
        fread(&key_check, sizeof(int), 1, ptab->file);
        fread(&par_check, sizeof(int), 1, ptab->file);
        if (par_check == key) return 1;
    }
    return -1;
}

int D_Add(Table *ptab) {

    unsigned int k;
    unsigned int park;
    printf("Enter key-->");
    scanf("%u", &k);
    scanf("%*c");
    printf("Enter parent's key-->");
    scanf("%u", &park);
    scanf("%*c");
    printf("Enter info-->");
    char *info = in_str();
    if (info == NULL) {
        return 0;
    }
    insert(ptab, k, park, info, 0);
    free(info);
    return 1;
}

int D_Show(Table *ptab) {
    if (ptab == NULL || ptab->csize == 0 || ptab->file == NULL) {
        printf("Table is empty\n");
        return 1;
    }
    else {
        printf("-------------------------------------------------\n");
        for (int i = 0; i < ptab->csize; i++) {
            int key, park, len_info;
            char *info = NULL;
            reading_ints(ptab, &key, &park, &len_info, i);
            reading(ptab, len_info, &info);
            printf("|\t%u\t|\t%u\t|\t%s\t|\n", key, park, info);
            free(info);
        }
        printf("-------------------------------------------------\n");

    }
}


int D_Del_table(Table *ptab) {
    fclose(ptab->file);
    free(ptab->shifts);
    free(ptab);
    return 1;
}





int D_Find(Table *ptab) {
    unsigned int key;
    printf("Enter key, which you want find-->");
    scanf("%u", &key);
    scanf("%*c");
    int ind = D_Find_key(ptab, key);
    if (ind != -1) {
        Table *table = create_table(100);
        int file_k, file_park, len_info;
        char *info = NULL;
        reading_ints(ptab, &file_k, &file_park, &len_info, ind);
        reading(ptab, len_info, &info);
        insert(table, file_k, file_park, info, 1);
        printf("These elements were found!\n");
        D_Show(table);
        D_Del_table(table);
        free(info);
    } else printf("Key doesn't exist\n");

}

int D_Find_By_Parents(Table *ptab) {
    if (ptab->csize == 0) {
        printf("Table is empty. Nothing found");
        return 1;
    }
    printf("Enter the range of parents keys-->\n");
    unsigned int min, max;
    scanf("%u %u", &min, &max);
    scanf("%*c");
    printf("%u %u\n", min, max);
    Table *find = create_table(100);
    for (int i = 0; i < ptab->csize; i++) {
        int f_key, f_par_key, len_info;
        char *info = NULL;
        reading_ints(ptab, &f_key, &f_par_key, &len_info, i);
        reading(ptab, len_info, &info);
        if (f_par_key <= max && f_par_key >= min) {
            insert(find, f_key, f_par_key, info, 1);
        }
        free(info);
    }
    printf("These elements were found!\n");
    D_Show(find);
    D_Del_table(find);
}

int D_Del(Table *ptab) {
    unsigned int k;
    printf("Enter key which you want delete-->");
    scanf("%u", &k);
    scanf("%*c");
    int ind = D_Find_key(ptab, k);
    int parent = D_Find_par(ptab, k);
    if (parent == -1) {
        if (ind != -1) {
            if (ind == ptab->csize - 1) {
                ptab->csize--;
                return 1;
            }
            for (int j = ind; j < ptab->csize - 1; j++) {
                ptab->shifts[j] = ptab->shifts[j+1];
            }
            ptab->csize--;
        } else printf("This key doesn't exist\n");
    } else printf("This key is parent of another\n");
}
