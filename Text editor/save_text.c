#include "message.h"

#include <stdio.h>
#include <string.h>
#include <curses.h>

void SaveText(WINDOW *win, const char *file_name, char **text, const int len_text){
    FILE *stream;

    stream = fopen(file_name,"w");

    if(stream == NULL){
        Message(win,"Error opening file for writing");
        return;
    }

    const char new_line = '\n';

    int i = 0, j = 0;

    for(i = 0; i < len_text; i++){
        for(j = 0; j < 256; j++){
            if(text[i][j] == '\0') break;
            fwrite(&text[i][j], sizeof(char), 1, stream);
        }
        if(j != 0) fwrite(&new_line, sizeof(char), 1, stream);
    }

    fclose(stream);
}