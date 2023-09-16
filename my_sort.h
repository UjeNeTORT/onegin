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
 * @brief giga swap  (WORKS ONLY FOR 64-bit systems)
 *
 *
 * @param [in]  aptr pointer to a-variable
 * @param [in]  bptr pointer to b-variable
 * @param [in]  size size of variables to get swapped
*/
void Swap(void *aptr, void *bptr, int size);

/**
 * @brief lexic cmp strings (asc order)
 *
 * @param [in]  str1 pointer to a-variable
 * @param [in]  str2 pointer to a-variable
 *
 * @return 1 if str1 >  str2
 *         0 if str1 == str2
 *        -1 if str1 <  str2
*/
int cmpStr (const void *str1, const void *str2);

/**
 * @brief lexicog cmp strings from their endings (asc order)
 *
 * @param [in]  str1 pointer to a-variable
 * @param [in]  str2 pointer to a-variable
 *
 * @return 1 if str1 >  str2 (from the back)
 *         0 if str1 == str2 (from the back)
 *        -1 if str1 <  str2 (from the back)
*/
int cmpRStr(const void *str1, const void *str2);

/**
 * @brief get address of el index of arr
 *
 * @param [in]  arr     array from which we take address
 * @param [in]  index   index (really?)
 * @param [in]  el_size size of 1 element
 *
*/
void *GetAddress(void *arr, int index, size_t el_size);

/**
 * @brief set pointer to a position where the first letter is
 *
 * @param [in]  str     string pointer
 * @param [in]  len     string len
*/
const char *DelNotAlpha (const char *str, int len);

/**
 * @brief set pointer to a position (from the back) where the first letter is
 *
 * @param [in]  str     pointer to the end of string (the symbol before \0)
 * @param [in]  len     string len
*/
const char *DelNotAlphaR(const char *str, int len);

#endif // MY_SORT_H
