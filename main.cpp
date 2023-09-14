#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

/*
TODO
я путаюсь как передавать строки в функции *(const char **)str           DONE
сделать скип знаков препинания                                          DONE
assert (ptr1 != ptr2)
БОЛЬШЕ const
мусор в конец
разбить на файлы
сделать quick sort
сделать чтобы функции ретернили enum (особенно компараторы для ошибок)
size_t
сделать cmd флаги

*/

#define LOG_MODE 0

//TODO make cmd args for this purpose
const char * const MASTERPIECE = "static/onegin.txt";

enum CMP_RES {
    CMP_RES_SMLLR = -1,
    CMP_RES_EQL = 0,
    CMP_RES_BGGR = 1,
    ERR_NULL_PTR
};

char **ParseLines(char *buf);
void WriteText(FILE *fp, const char **text, int n_lines);

int GetFileSize(FILE *file);
int CntNewLine(const char *buf);

void QuickSort(void * const data, int size, int el_size);
void BubbleSort (void * const data, int size, int el_size, int (*cmp) (const void *a, const void *b));
void Swap_(void *aptr, void *bptr, int size);

int cmpStr (const void * str1, const void * str2);
int cmpRStr(const void *str1, const void *str2);

void *GetAddress(const void *arr, int index, int el_size);
const char *DelNotAl(const char *str, int len);
const char *DelNotAlR(const char *str, int len);


int main() {
    // -------------- TO FUNCTION ----------------
    FILE *fin = fopen(MASTERPIECE, "rb");

    int f_size = GetFileSize(fin);

    char *buf = (char *) calloc(f_size + 1, sizeof(char));

    assert (buf);

    fread(buf, sizeof(char), f_size, fin);
    int new_lines = CntNewLine(buf);

    fclose(fin);
    // -------------------------------------------

    #if LOG_MODE
    FILE *log = fopen("debug_log.log", "w");
    for (int i = 0; i < f_size  + 1; i++)
        fprintf(log, "buf[i] = %c (%d)\n", buf[i], buf[i]);
    fclose(log);
    #endif // LOG_MODE

    char **text = ParseLines(buf);

    assert (text);

    #if LOG_MODE
    log = fopen("debug_log.log", "a");
    while (*text) {
        fprintf(log, "text = %p\n"
                     "%s\n", text, *text);
        text++;
    }
    fclose(log);
    #endif // LOG_MODE

    BubbleSort(text, new_lines, sizeof(char *), cmpRStr);

    FILE *fout = fopen("out.txt", "w");

    WriteText(fout, (const char **) text, new_lines);
    printf("vse\n"); //todelete
    fclose(fout);

    return 0;
}

char **ParseLines(char *buf) {
    assert (buf);

    if (!buf) {
        fprintf(stderr, "ParseLines: null pointer to buf received\n");
        return NULL;
    }

    int n_lines = CntNewLine(buf);

    char **l_ptrs = (char **) calloc(n_lines + 1, sizeof(char *));
    char **l_ptrs_ansc = l_ptrs;

    *l_ptrs_ansc++ = buf;

    while (*buf)
        if (*buf == '\r') {
            *buf++ = '\0';
            // skip \n after \r

            *l_ptrs_ansc++ = ++buf;
        }
        else if (*buf == '\n'){
            *buf++ = '\0';
            *l_ptrs_ansc++ = buf;
        }
        else {
            buf++;
        }

        return l_ptrs;
}

void WriteText(FILE *fp, const char **text, int n_lines) {
    assert (fp);
    assert (text);
    assert (n_lines >= 0);

    if (!fp) {
        fprintf(stderr, "WriteText: null pointer to file received\n");
        return ;
    }

    if (!text) {
        fprintf(stderr, "WriteText: null pointer to text received\n");
        return ;
    }

    if (n_lines < 0) {
        fprintf(stderr, "WriteText: n_lines < 0\n");
        return ;
    }

    for (int i = 0; i < n_lines; i++) {
        fprintf(fp, "%s\n", *text++);
    }

}

int GetFileSize(FILE *file) {
    assert (file);

    if (!file) {
        fprintf(stderr, "GetFileSize: null instead of file received\n");
        // return NULL;
    }

    int res = 0;

    fseek(file, 0, SEEK_END);
    res = ftell(file);
    rewind(file);

    return res;
}

int CntNewLine(const char *buf) {
    assert (buf);

    if (!buf) {
        fprintf(stderr, "CntNewLine: null pointer to buffer received\n");
        // return NULL;
    }

    int n_cnt = 0;

    while (*buf++)
        if (*buf == '\n') n_cnt++;

    return n_cnt;
}

/**
 * @param [out] data array we are going to sort
 * @param [in]  size amount of elements in data
*/
void QuickSort(void * const data, int size, int el_size) {
    return ;
}

// TODO quick_sort + return enum
/**
 * @param [out] data    array to be sorted
 * @param [in]  size    amount of elements in data
 * @param [in]  el_size size of 1 element
 * @param [in]  cmp     function-comparator
*/
void BubbleSort (void * const data, int size, int el_size, int (*cmp) (const void *a, const void *b)) {

    assert (data);
    assert (size >= 0);

    if (!data) {
        printf("BubbleSort: null pointer received\n");
        return ;
    }

    if (size < 0) {
        printf("BubbleSort: size of data array must be 0 or higher\n");
        return ;
    }

    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < size; j++) {

            // TOASK когда тут было cmp(&GetAdress(data, j, el_size), ...) почему он отсортировал не по возрастанию адресов?
            if (cmp((const void *) GetAddress(data, j,     el_size),
                    (const void *) GetAddress(data, j + 1, el_size)) > 0) {

                Swap_(GetAddress(data, j,     el_size),
                      GetAddress(data, j + 1, el_size), sizeof(void *));

            }
        }
    }
}

// not very optimal
void Swap_(void *aptr, void *bptr, int size) {

    assert(aptr);
    assert(bptr);

    if (!aptr) {
        fprintf(stderr, "Swap_: null pointer to a\n");
        return ;
    }

    if (!bptr) {
        fprintf(stderr, "Swap_: null pointer to b\n");
        return ;
    }

    unsigned long long temp = 0;
    int step = 0;

    while (size > 0)
    {

        if (size >> 3 > 0)
            step = sizeof(long long);
        else if (size >> 2 > 0)
            step = sizeof(int);
        else if (size >> 1 > 0)
            step = sizeof(short);
        else
            step = sizeof(char);

        memcpy(&temp, bptr, step);
        memcpy(bptr, aptr, step);
        memcpy(aptr, &temp, step);

        aptr = (char *) aptr + step;
        bptr = (char *) bptr + step;

        size -= step;

    }
}

// TOASK с (char **) не работает (answer: const ставить надо правильно)
int cmpStr(const void *str1, const void *str2) {
    assert(str1);
    assert(str2);

    if (!str1) {
        fprintf(stderr, "cmpStr: null pointer to a-str received");
        // return NULL;
    }

    if (!str2) {
        fprintf(stderr, "cmpStr: null pointer to b-str received");
        // return NULL;
    }

    int len1 = strlen(*(const char * const *) str1);
    int len2 = strlen(*(const char * const *) str2);

   if ((str1 = DelNotAl((const char *) str1, len1)) == NULL) return -1;
   if ((str2 = DelNotAl((const char *) str2, len2)) == NULL) return 1;

    #if LOG_MODE
    FILE *log = fopen("debug_log.log", "a");
    fprintf(log, "cmpStr: str1 = %p (%s)\n"
                 "        str2 = %p (%s)\n", str1, str1, str2, str2); // TOASK если в %s подставлять *(char **)str, ничего не робит
    fclose(log);
    #endif //LOG_MODE

    if (!str1 || !str2) return 0;

    return strcmp(*(const char * const *) str1, *(const char * const *) str2);
}

int cmpRStr(const void *str1, const void *str2) {
    assert (str1);
    assert (str2);

    if (!str1) {
        fprintf(stderr, "cmpStr: null pointer to a-str received");
        // return NULL;
    }

    if (!str2) {
        fprintf(stderr, "cmpStr: null pointer to b-str received");
        // return NULL;
    }

    const char *s1 = *(char * const *) str1;
    const char *s2 = *(char * const *) str2;

    int len1 = strlen(*(const char * const *) str1);
    int len2 = strlen(*(const char * const *) str2);

    s1 += len1;
    s2 += len2;

    s1 = DelNotAlR(s1, len1);
    s2 = DelNotAlR(s2, len2);

    while (len1 && len2 && *s1 == *s2) {
        s1--;
        s2--;
        len1--;
        len2--;
    }

    if (len1 && !len2) return 1;

    if (!len1 && len2) return -1;

    if (!s1 || !s2) return 0;

    return *s1 - *s2;

}

void *GetAddress(const void *arr, int index, int el_size) {
    assert (arr);
    assert (index >= 0);
    assert (el_size > 0);

    if (!arr) {
        fprintf(stderr, "GetAddress: null ptr to an arr received\n");
        return NULL;
    }

    if (index < 0) {
        fprintf(stderr, "GetAddress: invalid index received\n");
        return NULL;
    }

    if (el_size <= 0) {
        fprintf(stderr, "GetAddress: invalid el_size received\n");
        return NULL;
    }

    return (void *) ((const char *) arr + index * el_size);
}

const char *DelNotAl(const char *str, int len) {
    assert(str);
    assert (len >= 0);

    if (!str) {
        fprintf(stderr, "DelNotAl: null ptr to str received\n");
        return NULL;
    }

    if (len < 0) {
        fprintf(stderr, "DelNotAl: len less than 0 received\n");
        return NULL;
    }

    while (len-- > 0 && !isalpha(*str)) {
        str++;
    }

    return (len > 0) ? str : (const char *) NULL;
}

const char *DelNotAlR(const char *str, int len) {
    assert(str);
    assert (len >= 0);

    if (!str) {
        fprintf(stderr, "DelNotAl: null ptr to str received\n");
        return NULL;
    }

    if (len < 0) {
        fprintf(stderr, "DelNotAl: len less than 0 received\n");
        return NULL;
    }

    while (len-- > 0 && !isalpha(*str)) {
        str--;
    }

    return (len > 0) ? str : (const char *) NULL;
}
