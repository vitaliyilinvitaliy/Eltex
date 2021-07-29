#include "registration.h"

#include <ncurses.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20

int Registration(char *user_name){
    struct winsize window_size;

    ioctl(fileno(stdout), TIOCGWINSZ, (char*)&window_size);
    
    int width = window_size.ws_col;
    int height = window_size.ws_row;

    curs_set(TRUE);
    echo();

    refresh();

    int offsetx = (COLS - width) / 2;
    int offsety = (LINES - height) / 2;

    char name[MAX_NAME_LEN] = {0};

    WINDOW *win = newwin(height, width, offsety, offsetx);

    char hello[] = "Input your name: ";

    wmove(win, LINES/2, (COLS-strlen(hello))/2);
    wprintw(win ,"%s", hello);
    box(win, 0, 0);

    wrefresh(win);

    wgetnstr(win, user_name, MAX_NAME_LEN);
    
    curs_set(FALSE);
    noecho();
    refresh();

    delwin(win);
    refresh();
}