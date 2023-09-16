#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "text_buf.h"
#include "my_sort.h"

/*
TODO
я путаюсь как передавать строки в функции *(const char **)str           DONE (я лох палучаеццо)
сделать скип знаков препинания                                          DONE
БОЛЬШЕ const                                                            DONE
вывод буфера                                                            DONE
доки                                                                    DONE
разбить на файлы                                                        DONE
free                                                                    DONE
а если файл прочитали в режиме без rb и размери не сходятся             posle laby
сделать чтобы функции ретернили enum (особенно компараторы для ошибок)  saturday
size_t                                                                  DONE
тесты                                                                   posle laby
сделать quick sort                                                      saturday
delnotalpha (make it return enum)                                       posle laby
*/

const char * const MASTERPIECE = "static/onegin.txt";

int main() {

    char *buf = NULL;
    const char **text = NULL;
    int new_lines = ReadText(MASTERPIECE, &text, &buf);

    // -------------------------------------------

    qsort(text, new_lines, sizeof(char *), cmpStr);

    WriteText("out.txt", "w", text, new_lines);

    // -------------------------------------------

    qsort(text, new_lines, sizeof(char *), cmpRStr);

    WriteText("out.txt", "a", text, new_lines);

    // -------------------------------------------

    WriteBuf("out.txt", "a", buf, new_lines);

    printf("__ OOps, something went not wrong__");

    FreeText(text);
    FreeBuf(buf);

    return 0;
}

/*
                            ,--,           ,----,
,-.----.       ,----..   ,---.'|         ,/   .`|  ,----..                                               ,--,       ,--.
\    /  \     /   /   \  |   | :       ,`   .'  : /   /   \  ,-.----.      ,---,       .--.--.         ,--.'|   ,--/  /|   ,---,
|   :    \   /   .     : :   : |     ;    ;     //   .     : \    /  \    '  .' \     /  /    '.    ,--,  | :,---,': / '  '  .' \
|   |  .\ : .   /   ;.  \|   ' :   .'___,/    ,'.   /   ;.  \;   :    \  /  ;    '.  |  :  /`. / ,---.'|  : ':   : '/ /  /  ;    '.
.   :  |: |.   ;   /  ` ;;   ; '   |    :     |.   ;   /  ` ;|   | .\ : :  :       \ ;  |  |--`  |   | : _' ||   '   ,  :  :       \
|   |   \ :;   |  ; \ ; |'   | |__ ;    |.';  ;;   |  ; \ ; |.   : |: | :  |   /\   \|  :  ;_    :   : |.'  |'   |  /   :  |   /\   \
|   : .   /|   :  | ; | '|   | :.'|`----'  |  ||   :  | ; | '|   |  \ : |  :  ' ;.   :\  \    `. |   ' '  ; :|   ;  ;   |  :  ' ;.   :
;   | |`-' .   |  ' ' ' :'   :    ;    '   :  ;.   |  ' ' ' :|   : .  / |  |  ;/  \   \`----.   \'   |  .'. |:   '   \  |  |  ;/  \   \
|   | ;    '   ;  \; /  ||   |  ./     |   |  ''   ;  \; /  |;   | |  \ '  :  | \  \ ,'__ \  \  ||   | :  | '|   |    ' '  :  | \  \ ,'
:   ' |     \   \  ',  / ;   : ;       '   :  | \   \  ',  / |   | ;\  \|  |  '  '--' /  /`--'  /'   : |  : ;'   : |.  \|  |  '  '--'
:   : :      ;   :    /  |   ,/        ;   |.'   ;   :    /  :   ' | \.'|  :  :      '--'.     / |   | '  ,/ |   | '_\.'|  :  :
|   | :       \   \ .'   '---'         '---'      \   \ .'   :   : :-'  |  | ,'        `--'---'  ;   : ;--'  '   : |    |  | ,'
`---'.|        `---`                               `---`     |   |.'    `--''                    |   ,/      ;   |,'    `--''
  `---`                                                      `---'                               '---'       '---'
*/
