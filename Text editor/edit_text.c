#include "print_parameters.h"

#include <curses.h>
#include <string.h>
#include <sys/ioctl.h>

int EditText(WINDOW *win, char **text, const int len_text){
    int ch = -1;
    static int i = 0;
    int pos_x = 1, pos_y = 1;

    int x, y, len_str = 0;

    
    wmove(win, pos_y, pos_x);
    echo();
    curs_set(TRUE);
    wrefresh(win);

    /*Вынести перемещение по окну в отдельную функцию*/

    while (((ch = wgetch(win)) != KEY_F(12)) && (pos_y < len_text)) {
        switch (ch)
        {
        case KEY_BACKSPACE:
			if (0 == pos_x) break;
			getyx(win, y, x);
			mvwaddch(win, y, x, ' ');
			wrefresh(win);
			wmove(win, y, x);
			pos_y = y;
            pos_x = x;
            text[pos_y - 1][pos_x - 1] = ' ';
            break;
        case 10://'\n'
            //text[pos_y - 1][pos_x - 1] = '\n';
            pos_y++;
            pos_x = 1;
            wmove(win, pos_y, pos_x);            
            break;

        case KEY_UP:
            if(pos_y == 1) break;
            pos_y--;
            len_str = strlen(text[pos_y - 1]); 
            pos_x = (len_str == 0)? 1 : len_str;
            break;

        case KEY_DOWN:
            if(pos_y == len_text) break;
            pos_y++;
            len_str = strlen(text[pos_y - 1]);
            pos_x = (len_str == 0)? 1 : len_str;
            break;

        case KEY_RIGHT:
            if(pos_x == strlen(text[pos_y - 1])){
                if(pos_y == len_text) break;
                pos_y++;
                pos_x = 1;
                break;
            }
            pos_x++;
            break;

        case KEY_LEFT:
            if(pos_x == 1){
                if(pos_y == 1) break;
                pos_y--;
                pos_x = strlen(text[pos_y]);
                break;
            }
            pos_x--;
            break;

        default:
            text[pos_y - 1][pos_x - 1] = ch;
            text[pos_y - 1][pos_x] = '\0';
            pos_x++;
            break;
        }
        
        print_parameters(win, pos_y, pos_x, REGIME_INPUT);
	}

    curs_set(FALSE);
    noecho();
    return -1;
}