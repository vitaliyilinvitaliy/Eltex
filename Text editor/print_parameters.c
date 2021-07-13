#include "print_parameters.h"

#include <curses.h>
#include <sys/ioctl.h>
#include <string.h>

void print_parameters(WINDOW * win, int y_cursor, int x_cursor, int regime){
    struct winsize size;
    ioctl(fileno(stdout),TIOCGWINSZ,(char *) &size);

    wmove(win,size.ws_row - 1, 1);
    wprintw(win,"  Position: %d:%d\tRegime: %s  ", y_cursor, x_cursor, ((regime == REGIME_INPUT)? "Input" : "Command"));
    wmove(win, y_cursor, x_cursor);

    //refresh();
}