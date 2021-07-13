#include "print_parameters.h"

#include <curses.h>
#include <sys/ioctl.h>
#include <string.h>

void GetFileName(WINDOW *win, char *file_name){
    WINDOW *subwindow;

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
    
    print_parameters(win, 0, 0, REGIME_INPUT);
    wrefresh(win);
    
    echo();
    curs_set(TRUE);

    wmove(win,size.ws_row - 1, 2);
    wprintw(win,"Enter file name:                     ");
    wmove(win,size.ws_row - 1, 18);

    wscanw(win,"%s30",file_name);

    noecho();
    curs_set(FALSE);
}