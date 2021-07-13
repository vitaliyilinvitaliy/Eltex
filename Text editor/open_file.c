#include "message.h"

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/ioctl.h>

void OpenFile(WINDOW *win, const char *filename, char **text, const int len_text){
    FILE *stream = NULL;

    stream = fopen(filename,"r");

    if(stream == NULL){
        Message(win,"File or directory not found!");
        return;
    }

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);

    int y = 1, i = 0;

    while(!feof(stream)){
        fgets(text[i], 256, stream);
        i++;
    }

    
    for(int str_number = 0; str_number < y && str_number < (size.ws_col - 2); str_number++, y++){
        wmove(win, y, 1);
        wprintw(win,"%s",text[str_number]);
    }

    wrefresh(win);

    fclose(stream);
}