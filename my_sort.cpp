#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_sort.h"


// NOT FINISHED
void QuickSort (void *data, int size, size_t el_size, int (*cmp) (const void *a, const void *b)) {

    assert (data);
    assert (size > 0);
    assert (el_size > 0);
    assert (cmp);


    if (!data) {
        fprintf(stderr, "QuickSort: null pointer received\n");
        return ;
    }

    if (size <= 0) {
        fprintf(stderr, "QuickSort: size of data array must be 0 or higher\n");
        return ;
    }

    if (el_size <= 0) {
        fprintf(stderr, "QuickSort: el_size <= n");
        return ;
    }

    if (!cmp) {
        fprintf(stderr, "QuickSort: null pointer to comparator received\n");
        return ;
    }

    qsort (data, size, el_size, cmp);

    /*
    Анекдот:

    Журналисты пошли снимать сюжет в деревню. Они встретили фермера с двумя коровами и взяли у него интервью:
    -Добрый вечер, такие большие коровы, сколько они едят сена в день?
    -Какая из них? Черная или коричневая?
    -Ну коричневая
    -Несколько килограммов в день
    -А черная?
    -Несколько килограммов в день

    Журналист смутился, но продолжил интервью.
    -Сколько молока дают?
    -Какая? Черная или коричневая?
    -Черная
    -Ну литра два
    -А коричневая?
    -Ну литра два

    Журналист разозлился:
    -ПОЧЕМУ ВЫ ПОСТОЯННО СПРАШИВАЕТЕ КАКАЯ КОРОВА, ЕСЛИ ОНИ ОДИНАКОВЫЕ?
    -Потому что черная - моя
    -А коричневая?
    -Тоже моя

    */

    return ;
}

void BubbleSort (void *data, int size, size_t el_size, int (*cmp) (const void *a, const void *b)) {

    assert (data);
    assert (size > 0);
    assert (el_size > 0);
    assert (cmp);

    if (!data) {
        fprintf(stderr, "BubbleSort: null pointer received\n");
        return ;
    }

    if (size <= 0) {
        fprintf(stderr, "BubbleSort: size of data array must be 0 or higher\n");
        return ;
    }

    if (el_size <= 0) {
        fprintf(stderr, "BubbleSort: el_size <= n");
        return ;
    }

    if (!cmp) {
        fprintf(stderr, "BubbleSort: null pointer to comparator received\n");
        return ;
    }

    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < size; j++) {

            if (cmp(GetAddress(data, j,     el_size),
                    GetAddress(data, j + 1, el_size)) > 0) {

                Swap(GetAddress(data, j,     el_size),
                      GetAddress(data, j + 1, el_size), sizeof(void *));

            }
        }
    }
}

// swaps your braincells when you try to understand what it does
void Swap(void *aptr, void *bptr, int size) {

    assert(aptr);
    assert(bptr);

    if (!aptr) {
        fprintf(stderr, "Swap: null pointer to a\n");
        return ;
    }

    if (!bptr) {
        fprintf(stderr, "Swap: null pointer to b\n");
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

    const char *s1 = *(char * const *) str1;
    const char *s2 = *(char * const *) str2;

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    s1 = DelNotAlpha(s1, len1);
    s2 = DelNotAlpha(s2, len2);

    if (!str1 || !str2) return 0;

    return strcmp(s1, s2);
}

int cmpRStr(const void *str1, const void *str2) {
    assert (str1);
    assert (str2);

    if (!str1) {
        fprintf(stderr, "cmpStr: null pointer to a-str received");

    }

    if (!str2) {
        fprintf(stderr, "cmpStr: null pointer to b-str received");

    }


    const char *s1 = *(char * const *) str1;
    const char *s2 = *(char * const *) str2;

    int len1 = strlen(s1);
    int len2 = strlen(s2);

    s1 += len1;
    s2 += len2;


    s1 = DelNotAlphaR(s1, len1);
    s2 = DelNotAlphaR(s2, len2);

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

void *GetAddress(void *arr, int index, size_t el_size) {
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

const char *DelNotAlpha(const char *str, int len) {
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

const char *DelNotAlphaR(const char *str, int len) {
    assert(str);
    assert (len >= 0);

    if (!str) {
        fprintf(stderr, "DelNotAl: null ptr to str received\n");

    }

    if (len < 0) {
        fprintf(stderr, "DelNotAl: len less than 0 received\n");

    }

    while (len-- > 0 && !isalpha(*str)) {
        str--;
    }

    return str;
}
