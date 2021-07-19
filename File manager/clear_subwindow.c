#include <curses.h>

void ClearSbw(WINDOW *win, unsigned short int horizontal, unsigned short int vertical){
    
    for(int i = 1; i < vertical; i++){
        for(int j = 1; j < horizontal; j++){
            wattron(win,COLOR_PAIR(2));
            mvwaddch(win, j, i, ' ');
        }
    }
    wrefresh(win);
}