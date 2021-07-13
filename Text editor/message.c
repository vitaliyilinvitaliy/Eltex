#include "clear_screen.h"

#include <curses.h>
#include <sys/ioctl.h>
#include <string.h>

void Message(WINDOW *win, const char *message_text){

    ClearScreen(win);

    noecho();
    curs_set(FALSE);

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);

    wmove(win,size.ws_row - 1, 1);
    wprintw(win,"                                    ");
    wmove(win,size.ws_row - 1, 2);
    wprintw(win,"Message: %s",message_text);
    
    wmove(win,1, 1);
    wprintw(win,"...Press any key...",message_text);
    wgetch(win);

    ClearScreen(win);
}