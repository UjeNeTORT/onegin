#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "text_buf.h"
#include "my_sort.h"

const char * const MASTERPIECE = "static/onegin.txt";

int main() {

    char *buf = NULL;
    const char **text = NULL;
    int new_lines = ReadText(MASTERPIECE, &text, &buf);

    // -------------------------------------------

    BubbleSort(text, new_lines, sizeof(char *), cmpStr);

    WriteText("out.txt", "w", text, new_lines);

    // -------------------------------------------

    qsort(text, new_lines, sizeof(char *), cmpRStr);

    WriteText("out.txt", "a", text, new_lines);

    // -------------------------------------------

    WriteBuf("out.txt", "a", buf, new_lines);

    printf("__ OOps, something went not wrong__\n");

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
