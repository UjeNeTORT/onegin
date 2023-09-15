#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_sort.h"


// NOT FINISHED
void QuickSort (void *data, int size, int el_size, int (*cmp) (const void *a, const void *b)) {
    assert (data);
    assert (size > 0);
    assert (el_size > 0);
    assert (cmp);

    qsort (data, size, el_size, cmp);

    return ;
}

// TODO quick_sort + return enum
void BubbleSort (void *data, int size, int el_size, int (*cmp) (const void *a, const void *b)) {

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

            if (cmp(GetAddress(data, j,     el_size),
                    GetAddress(data, j + 1, el_size)) > 0) {

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

        if      ((size >> 3) > 0) step = sizeof(long long);
        else if ((size >> 2) > 0) step = sizeof(int);
        else if ((size >> 1) > 0) step = sizeof(short);
        else                      step = sizeof(char);

        memcpy(&temp, bptr, step);
        memcpy(bptr, aptr, step);
        memcpy(aptr, &temp, step);

        aptr = (char *) aptr + step;
        bptr = (char *) bptr + step;

        size -= step;

    }
}


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

    const char *s1 = *(const char **) str1;
    const char *s2 = *(const char **) str2;

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    s1 = DelNotAl(s1, len1);
    s2 = DelNotAl(s2, len2);

    if (!str1 || !str2) return 0;

    return strcmp(*(char * const *) str1, *(char * const *) str2);
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


    const char *s1 = *(const char **) str1;
    const char *s2 = *(const char **) str2;

    int len1 = strlen(s1);
    int len2 = strlen(s2);

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

void *GetAddress(void *arr, int index, int el_size) {
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

    return (char *) arr + index * el_size;
}

const char *DelNotAl(const char *str, int len) {
    assert (str);
    assert (len >= 0);

    if (!str) {
        fprintf(stderr, "DelNotAl: null ptr to str received\n");

    }

    if (len < 0) {
        fprintf(stderr, "DelNotAl: len less than 0 received\n");

    }

    while (len-- > 0 && !isalpha(*str)) {
        str++;
    }

    return str;
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

    return str;
}
