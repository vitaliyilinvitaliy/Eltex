#include <ncurses.h>

static int w_x = 0;
static int w_y = 0;
static int w_horiz = 0;
static int w_vertic = 0;

int InitChat(WINDOW *chat, int x, int y, int horizontal, int vertical){
    chat = newwin(vertical, horizontal , y, x);
    keypad(chat, TRUE);
    box(chat, 0 , 0);
    wrefresh(chat);

    w_x = x;
    w_y = y;
    w_horiz = horizontal;
    w_vertic = vertical;

    return 0;
}
