#include "sig_winch.h"
#include "edit_text.h"
#include "print_parameters.h"
#include "open_file.h"
#include "save_text.h"
#include "get_file_name.h"
#include "clear_screen.h"

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void window(const char *file_name){
    WINDOW *wnd;
    WINDOW *wndscroll;

    char **text;
    int ch = -1;
    const int len_text = 100;

    char file_name_input[30];

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);

    initscr();
    signal(SIGWINCH, SigWinch);
    
    wnd = newwin(size.ws_row, size.ws_col, 0, 0);

    curs_set(FALSE);
    noecho();
    keypad(wnd, TRUE);

    box(wnd, 0, 0);
    wrefresh(wnd);

    text = (char**)calloc(sizeof(char*), len_text);
    for(int i = 0; i < len_text; i++) text[i] = (char*) calloc(sizeof(char), 256);

    print_parameters(wnd,0,0,REGIME_COMMAND);


    while((ch = wgetch(wnd)) != KEY_F(3)){
        switch (ch)
        {
        case KEY_F(12):
            print_parameters(wnd,0,0,REGIME_INPUT);
            EditText(wnd, text, len_text);
            break;

        case KEY_F(1):
            GetFileName(wnd,file_name_input);
            OpenFile(wnd, file_name_input, text, len_text);
            memset(file_name_input,0,30);
            break;

        case KEY_F(2):
            GetFileName(wnd,file_name_input);
            SaveText(wnd, file_name_input, text, len_text);
            memset(file_name_input,0,30);
            break;    
    
        case KEY_F(4):
            ClearScreen(wnd);
            break;
        default:
            break;
        }

        print_parameters(wnd,0,0,REGIME_COMMAND);
    }

    
    for(int i = 0; i < len_text; i++){
        free(text[i]);
    }

    free(text);

    delwin(wnd);
    endwin();
    exit(EXIT_SUCCESS);
}