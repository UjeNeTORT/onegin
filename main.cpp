#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_MODE 0


char **ParseLines(char *buf);

int GetFileSize(FILE *file);
int CntNewLine(char *buf);

void BubbleSort (void ** const arr, int size, int (*cmp) (const char *, const char *));
void Swap_(void *aptr, void *bptr, int size);


int main() {

    FILE *fp = fopen("static/floyd.txt", "rb");

    int f_size = GetFileSize(fp);

    char *buf = (char *) calloc(f_size + 1, sizeof(char));

    fread(buf, sizeof(char), f_size, fp);
    int new_lines = CntNewLine(buf);

    fclose(fp);

    #if DEBUG_MODE
    FILE *log = fopen("debug_log.log", "w");
    for (int i = 0; i < f_size  + 1; i++)
        fprintf(log, "buf[i] = %c (%d)\n", buf[i], buf[i]);
    fclose(log);
    #endif // DEBUG_MODE

    char **text = ParseLines(buf);

    #if DEBUG_MODE
    log = fopen("debug_log.log", "a");
    while (*text) {
        fprintf(log, "text = %p\n"
                     "%s\n", text, *text);
        text++;
    }
    fclose(log);
    #endif // DEBUG_MODE

    BubbleSort((void **) text, new_lines, strcmp);

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

void BubbleSort (void ** const arr, int size, int (*cmp) (const char *, const char *)) {
    #if DEBUG_MODE

    assert (arr);
    assert (size >= 0);

    #else

    if (!arr) {
        printf("BubbleSort: null pointer received\n");
        return ;
    }

    if (size < 0) {
        printf("BubbleSort: size of array must be 0 or higher\n");
        return ;
    }

    #endif // DEBUG_MODE

    printf("test1: size = %d\n", size);
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {

            printf("i = %d, j = %d\n", i, j);

            if ((*cmp)((char *) arr[j], (char *) arr[j + 1]) > 0) {
                Swap_((char *) arr[j], (char *) arr[j + 1], sizeof(char *));

            }
        }
    }
}

void Swap_(void *aptr, void *bptr, int size)
{

    unsigned long long temp = 0;
    int step = 0;

    while (size > 0)
    {
        memcpy(&temp, bptr, step);
        memcpy(bptr, aptr, step);
        memcpy(aptr, &temp, step);

        aptr = (char *) aptr + step;
        bptr = (char *) bptr + step;

        size -= step;

    }
}
