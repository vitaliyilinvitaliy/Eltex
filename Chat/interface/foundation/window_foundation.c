#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdio.h>

int InitFoundation(WINDOW *win){
    struct winsize sizews;

    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &sizews);

    refresh();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    win = newwin(5, 23, 2, 2);
    wbkgd(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);

    /*win = newwin(sizews.ws_row, sizews.ws_col, 0, 0);
    keypad(win, TRUE);
    box(win, 0 , 0);*/

    //wrefresh(win);

    return 0;
}