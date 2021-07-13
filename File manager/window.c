#include "sig_winch.h"
#include "size_window.h"

#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>

void window(void){
    WINDOW *foundation;
    WINDOW *left;
    WINDOW *right;
    WINDOW *activ;

    int ch = 0;
    struct size_window *size_l_r;

    size_l_r = calloc(sizeof(struct size_window), 1);

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
   
    SizeWindow(size_l_r);
    
    initscr();
    signal(SIGWINCH, SigWinch);
    noecho();
    curs_set(FALSE);
    refresh();

    foundation = newwin(size.ws_row, size.ws_col, 0,0);
    box(foundation, 0, 0);
    keypad(foundation, TRUE);
    wrefresh(foundation);

    left = derwin(foundation, size_l_r->l_vertical, size_l_r->l_horizontal, size_l_r->l_x , size_l_r->l_y);
    box(left, 0, 0);
    keypad(left, TRUE);
    wrefresh(left);
    

    right = derwin(foundation, size_l_r->r_vertical, size_l_r->r_horizontal, size_l_r->r_y , size_l_r->r_x);
    box(right, 0, 0);
    keypad(right, TRUE);
    wrefresh(right);

    while((ch = wgetch(foundation)) != KEY_F(1)){

    }

    echo();
    curs_set(TRUE);
    endwin();
}