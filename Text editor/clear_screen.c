#include <curses.h>
#include <sys/ioctl.h>

void ClearScreen(WINDOW *win){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);

    int i = 0, j = 0;

    for(i = 1; i < size.ws_row - 2; i++){
        wmove(win,i,j);
        for(j = 1; j < size.ws_col - 2; j++){
            mvwaddch(win, i, j, ' ');
        }
    }  
}