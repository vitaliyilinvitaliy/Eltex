#include "color_string.h"

#include <curses.h>

void ColorString(WINDOW *win, char *str, int number, int state){
    wmove(win,number + 1, 1);
    if(state == ON_STR){
        wattron(win, COLOR_PAIR(5));
        wprintw(win,"%s",str);
    }else{
        if(str[0] == '/'){
            wattron(win, COLOR_PAIR(3));
            wprintw(win,"%s",str);
            wattroff(win, COLOR_PAIR(3));
        }else{
            wattron(win, COLOR_PAIR(4));
            wprintw(win,"%s",str);
            wattroff(win, COLOR_PAIR(4));
        }
    }
    wrefresh(win);
}