#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "my_sort.h"

/*
TODO
я путаюсь как передавать строки в функции *(const char **)str           DONE
сделать скип знаков препинания                                          DONE
assert (ptr1 != ptr2)
БОЛЬШЕ const                                                            POLNY BAN
вывод буфера
доки
(мусор в конец)
разбить на файлы                                                        DONE
сделать quick sort
сделать чтобы функции ретернили enum (особенно компараторы для ошибок)
size_t
сделать cmd флаги
*/

//TODO make cmd args for this purpose
const char * const MASTERPIECE = "static/onegin.txt";

int ReadText(const char * const file, const char ***text);
int ReadBuf(const char * const file, char **buf);
const char **ParseLines(char *buf);
void WriteText(FILE *fp, const char **text, int n_lines);

int GetFileSize(FILE *file);
int CntNewLine(const char *buf);

int main() {

    const char **text = NULL;
    int new_lines = ReadText(MASTERPIECE, &text);

    // -------------- TO FUNCTION ----------------
    FILE *fout = fopen("out.txt", "w");

    WriteText(fout, text, new_lines);

    BubbleSort(text, new_lines, sizeof(char *), cmpStr);

    WriteText(fout, text, new_lines);

    printf("vse\n"); //todelete

    BubbleSort(text, new_lines, sizeof(char *), cmpRStr);

    WriteText(fout, text, new_lines);

    printf("Rvse\n"); //todelete

    fclose(fout);
    // -------------------------------------------

    return 0;
}

int ReadText(const char * const file, const char ***text) {
    char *buf = NULL;

    ReadBuf(file, &buf);

    int new_lines = CntNewLine(buf);

    *text = ParseLines(buf);

    return new_lines;
}

int ReadBuf(const char * const file, char **buf) {
    FILE *fin = fopen(file, "rb");

    int f_size = GetFileSize(fin);

    *buf = (char *) calloc(f_size + 1, sizeof(char));

    fread(*buf, sizeof(char), f_size, fin);

    fclose(fin);

    return CntNewLine((const char *) buf);
}

const char **ParseLines(char *buf) {
    assert (buf);

    if (!buf) {
        fprintf(stderr, "ParseLines: null pointer to buf received. Destroying the notebook.\n");
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

        return (const char **) l_ptrs;
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

    fseek(file, 0, SEEK_END);
    int res = ftell(file);
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
