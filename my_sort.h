#ifndef MY_SORT_H
#define MY_SORT_H

/**
 * @param [out] data    array to be sorted
 * @param [in]  size    amount of elements in data
 * @param [in]  el_size size of 1 element
 * @param [in]  cmp     function-comparator
*/
void QuickSort  (void *data, int size, size_t el_size, int (*cmp) (const void *a, const void *b));

/**
 * @param [out] data    array to be sorted
 * @param [in]  size    amount of elements in data
 * @param [in]  el_size size of 1 element
 * @param [in]  cmp     function-comparator
*/
void BubbleSort (void *data, int size, size_t el_size, int (*cmp) (const void *a, const void *b));

/**
 * @brief giga swap
*/
void Swap_(void *aptr, void *bptr, int size);

/**
 * @brief lexic cmp strings (asc order)
*/
int cmpStr (const void *str1, const void *str2);

/**
 * @brief lexicog cmp strings from their endings (asc order)
*/
int cmpRStr(const void *str1, const void *str2);

/**
 * @brief get address of el index of arr
*/
void *GetAddress(void *arr, int index, size_t el_size);

/**
 * @brief set pointer to a position where the first letter is
*/
const char *DelNotAlpha (const char *str, int len);

/**
 * @brief set pointer to a position (from the back) where the first letter is
*/
const char *DelNotAlphaR(const char *str, int len);

#endif // MY_SORT_H
