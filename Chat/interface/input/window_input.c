#include "../../message/send_message.h"

#include <ncurses.h>
#include <stdlib.h>

static int w_x = 0;
static int w_y = 0;
static int w_horiz = 0;
static int w_vertic = 0;

int InitInput(int x, int y, int horizontal, int vertical){
    w_x = x;
    w_y = y;
    w_horiz = horizontal;
    w_vertic = vertical;

    return 0;
}

int Input(WINDOW *win, struct my_parameters *params){
    char *message = NULL;
    int pos_x = 1, pos_y = 1, pos = 0;
    int x = 0, y = 0;
    int ch = -1;

    message = calloc(sizeof(char), (w_vertic - 2) * (w_horiz - 2));

    if(message == NULL){
        return 1;
    }

    wmove(win, 0, 1);
    wprintw(win, " %s ", (*params).name);
    wmove(win, pos_y, pos_x);
    wrefresh(win);

    while((ch = wgetch(win)) != KEY_F(1)){
        switch(ch){
            case KEY_BACKSPACE:
                if(pos_x == 1) break;
                
                pos_x--;
                pos--;
                message[pos] = ' ';
                mvwaddch(win, pos_y, pos_x, ' ');
                wmove(win, pos_y, pos_x);
                wrefresh(win);
                break;

            case 10://'\n'
                SendMessageSystemV(message, (*params));
                pos = 0;
                pos_x = 1;
                pos_y = 1;

                for(int i = 1; i < w_vertic - 1; i++){
                    for(int j = 1; j < w_horiz - 1; j++){
                        mvwaddch(win, i, j, ' ');
                    }
                }
                box(win, 0 , 0);
                wmove(win, 0, 1);
                wprintw(win, " %s ", (*params).name);
                wmove(win, pos_y, pos_x);
                wrefresh(win);

                break;

            default:
                if(pos_x == (w_horiz - 2)){
                    if(pos_y == (w_vertic - 2)) break;
                    message[pos] = ch;
                    mvwaddch(win, pos_y, pos_x, ch);
                    pos_y++;
                    pos_x = 1;
                    pos += w_horiz;
                    wmove(win, pos_y, pos_x); 
                }else{
                    message[pos] = ch;
                    mvwaddch(win, pos_y, pos_x, ch);
                    pos++;
                    pos_x++;
                    wmove(win, pos_y, pos_x);
                }
                break;
        }
        refresh();
    }

    free(message);
    return 0;
}

