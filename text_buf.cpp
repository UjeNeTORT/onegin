#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "text_buf.h"

static int ReadBuf(const char * const file, char **buf);

static int GetFileSize(FILE *file);
static int CntNewLine(const char *buf);

int ReadText(const char * const file, const char ***text, char **buf) {
    assert (file);
    assert (text);
    assert (buf);

    if (!file) {
        fprintf(stderr, "ReadText: file null received\n");
    }

    if (!text) {
        fprintf(stderr, "ReadText: text null received\n");
    }

    if (!buf) {
        fprintf(stderr, "ReadText: buf null received\n");
    }

    ReadBuf(file, buf);

    int new_lines = CntNewLine(*buf);

    *text = ParseLines(*buf);

    return new_lines;
}

int ReadBuf(const char * const file, char **buf) {
    assert (file);
    assert (buf);

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

void FreeText(void *text) {
    assert (text);

    free(text);
}

void FreeBuf(void *buf) {
    assert (buf);

    free(buf);
}

void WriteText(const char * const file, const char * const mode, const char **text, int n_lines) {
    assert (file);
    assert (text);
    assert (n_lines >= 0);

    if (!file) {
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

    FILE *fout = fopen(file, mode);

    while (n_lines-- > 0)
        fprintf(fout, "%s\n", *text++);

    fclose(fout);

}

void WriteBuf(const char * const file, const char * const mode, const char *buf, int n_lines) {
    assert (file);
    assert (buf);
    assert (n_lines >= 0);

    FILE *fout = fopen(file, mode);

    while (n_lines-- > 0) {
        fprintf(fout, "%s\n", buf);

        // skip string + \0 + \n
        buf += strlen(buf) + 2;
    }

    fclose(fout);
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
