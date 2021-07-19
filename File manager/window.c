#include "sig_winch.h"
#include "size_window.h"
#include "dir_list.h"
#include "subwindow.h"
#include "print_dir_list.h"

#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void window(void){
    WINDOW *foundation;
    WINDOW *left;
    WINDOW *right;
    WINDOW *activ;

    int ch = 0;
    struct size_window *size_l_r;
    struct attr_subwindow atsubw;

    char dir_l[256] = ".";
    char dir_r[256] = ".";

    char dir[256] = ".";

    size_l_r = calloc(sizeof(struct size_window), 1);

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
   
    SizeWindow(size_l_r);
    
    initscr();
    signal(SIGWINCH, SigWinch);
    noecho();
    curs_set(FALSE);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);

    foundation = newwin(size.ws_row, size.ws_col, 0,0);
    box(foundation, 0, 0);
    keypad(foundation, TRUE);
    wrefresh(foundation);
    
    left = derwin(foundation, size_l_r->l_vertical, size_l_r->l_horizontal, size_l_r->l_x , size_l_r->l_y);
    box(left, 0, 0);
    keypad(left, TRUE);
    wrefresh(left);
    PrintDirListDefault(left);
    
    right = derwin(foundation, size_l_r->r_vertical, size_l_r->r_horizontal, size_l_r->r_y , size_l_r->r_x);
    box(right, 0, 0);
    keypad(right, TRUE);
    wrefresh(right);
    PrintDirListDefault(right);

    activ = left;
    atsubw.horizontal =  size_l_r->l_horizontal;
    atsubw.vertical =  size_l_r->l_vertical;
    
    halfdelay(1);
    //(ch = wgetch(activ)) != KEY_F(1)
    while((ch = Subwindow(activ, dir, atsubw)) != KEY_F(1)){
        
        
        switch (ch)
        {
        case '\t':
            if(activ == left){
                activ = right;
                atsubw.horizontal =  size_l_r->r_horizontal;
                atsubw.vertical =  size_l_r->r_vertical;
                strcpy(dir_l, dir);
                strcpy(dir, dir_r);
            }else{
                activ = left;
                atsubw.horizontal =  size_l_r->l_horizontal;
                atsubw.vertical =  size_l_r->l_vertical;
                strcpy(dir_r, dir);
                strcpy(dir, dir_l);
            } 
            break;
        case REFRESH_WIN:
            noecho();
            curs_set(FALSE);

            refresh();
            box(foundation, 0, 0);
            keypad(foundation, TRUE);
            wrefresh(foundation);
            
            box(left, 0, 0);
            keypad(left, TRUE);
            wrefresh(left);
            PrintDirListDefault(left);
            
            box(right, 0, 0);
            keypad(right, TRUE);
            wrefresh(right);
            PrintDirListDefault(right);
            break;
        default:
            break;
        }
        
    }
   

    echo();
    curs_set(TRUE);
    delwin(left);
    delwin(right);
    delwin(foundation);

    endwin();
}