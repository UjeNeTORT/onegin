#ifndef TEXT_BUF_H
#define TEXT_BUF_H

/**
 * @brief read text from file to buf. then put ptrs to str beginnings to text arr
*/
int ReadText(const char * const file, const char ***text, char **buf);

/**
 * @brief write in file no more then n_lines strings pointers to which are in text
*/
void WriteText(const char * const file, const char * const mode, const char **text, int n_lines);

/**
 * @brief write in file no more then n_lines strings from buf (from \0 to \0)
*/
void WriteBuf(const char * const file, const char * const mode, const char *buf, int n_lines);

/**
 * @brief set all \rs to \0 (if no \r, set \ns to \0)
*/
const char **ParseLines(char *buf);

/**
 * @brief free text (шок)
*/
void FreeText(void *text);

/**
 * @brief free buf (шок)
*/
void FreeBuf(void *buf);

#endif // TEXT_BUF_H
