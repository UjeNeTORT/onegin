#ifndef MY_SORT_H
#define MY_SORT_H

enum CMP_RES {
    CMP_RES_SMLLR = -1,
    CMP_RES_EQL = 0,
    CMP_RES_BGGR = 1,
    ERR_NULL_PTR
};

/**
 * @param [out] data    array to be sorted
 * @param [in]  size    amount of elements in data
 * @param [in]  el_size size of 1 element
 * @param [in]  cmp     function-comparator
*/
void QuickSort  (void *data, int size, int el_size, int (*cmp) (const void *a, const void *b));

/**
 * @param [out] data    array to be sorted
 * @param [in]  size    amount of elements in data
 * @param [in]  el_size size of 1 element
 * @param [in]  cmp     function-comparator
*/
void BubbleSort (void *data, int size, int el_size, int (*cmp) (const void *a, const void *b));

/**
 *
*/
void Swap_(void *aptr, void *bptr, int size);

/**
 *
*/
int cmpStr (const void *str1, const void *str2);

/**
 *
*/
int cmpRStr(const void *str1, const void *str2);

/**
 *
*/
void *GetAddress(void *arr, int index, int el_size);

/**
 *
*/
const char *DelNotAlpha (const char *str, int len);

/**
 *
*/
const char *DelNotAlphaR(const char *str, int len);

#endif // MY_SORT_H
