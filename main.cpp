#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_MODE 0


char **ParseLines(char *buf);
void WriteText(FILE *fp, char **text, int n_lines);

int GetFileSize(FILE *file);
int CntNewLine(char *buf);

void QuickSort(void * const data, int size, int el_size);
void BubbleSort (void * const data, int size, int el_size, int (*cmp) (const void *a, const void *b));
void Swap_(void *aptr, void *bptr, int size);

int cmpStr(const void * str1, const void * str2);

void *GetAddress(void * arr, int index, int el_size);


int main() {
    // -------------------------------------------
    FILE *fp = fopen("static/floyd.txt", "rb");

    int f_size = GetFileSize(fp);

    char *buf = (char *) calloc(f_size + 1, sizeof(char));

    fread(buf, sizeof(char), f_size, fp);
    int new_lines = CntNewLine(buf);

    fclose(fp);
    // -------------------------------------------

    #if LOG_MODE
    FILE *log = fopen("debug_log.log", "w");
    for (int i = 0; i < f_size  + 1; i++)
        fprintf(log, "buf[i] = %c (%d)\n", buf[i], buf[i]);
    fclose(log);
    #endif // LOG_MODE

    char **text = ParseLines(buf);

    #if LOG_MODE
    log = fopen("debug_log.log", "a");
    while (*text) {
        fprintf(log, "text = %p\n"
                     "%s\n", text, *text);
        text++;
    }
    fclose(log);
    #endif // LOG_MODE

    BubbleSort(text, new_lines, sizeof(char *), cmpStr);

    FILE *fout = fopen("out.txt", "w");

    WriteText(fout, text, new_lines);

    fclose(fout);

    return 0;
}

char **ParseLines(char *buf) {
    assert (buf);

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

void WriteText(FILE *fp, char **text, int n_lines) {
    assert (text);
    assert (n_lines >= 0);

    for (int i = 0; i < n_lines; i++) {
        fprintf(fp, "%s\n", *text++);
    }

}

int GetFileSize(FILE *file) {
    assert (file);

    int res = 0;

    fseek(file, 0, SEEK_END);
    res = ftell(file);
    rewind(file);

    return res;
}

int CntNewLine(char *buf) {
    assert (buf);

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

            // TOASK когда тут было cmp(GetAdress(data, j, el_size), ...) почему он отсортировал не по возрастанию адресов?
            if (cmp(*(char **) GetAddress(data, j,     el_size),
                    *(char **) GetAddress(data, j + 1, el_size)) > 0) {

                Swap_(GetAddress(data, j,     el_size),
                      GetAddress(data, j + 1, el_size), sizeof(void *));

            }
        }
    }
}

// not very optimal
void Swap_(void *aptr, void *bptr, int size)
{

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

// TOASK с (char **) не работает
int cmpStr(const void *str1, const void *str2) {
    assert(str1);
    assert(str2);

    #if LOG_MODE
    FILE *log = fopen("debug_log.log", "a");
    fprintf(log, "cmpStr: str1 = %p (%s)\n"
                 "        str2 = %p (%s)\n", str1, str1, str2, str2); // TOASK если в %s подставлять *(char **)str, ничего не робит
    fclose(log);
    #endif //LOG_MODE

    return strcmp((const char *) str1, (const char *) str2);
}

void *GetAddress(void * arr, int index, int el_size) {
    return (char *) arr + index * el_size;
}
