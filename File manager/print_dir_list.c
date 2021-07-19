#include "dir_list.h"

#include <curses.h>
#include <string.h>

void PrintDirList(WINDOW *win, char** dir_list, int len_list){
    
    if(dir_list == NULL){
        return;
    }

    for(int i = 0; i < len_list; i++){
        wmove(win, i + 1, 1);
        if(dir_list[i][0] == '/'){
            wattron(win, COLOR_PAIR(3));
            wprintw(win, "%s", dir_list[i]);
            wattroff(win, COLOR_PAIR(3));
        }else{
            wattron(win, COLOR_PAIR(4));
            wprintw(win, "%s", dir_list[i]);
            wattroff(win, COLOR_PAIR(4));
        }
        
    }

    wrefresh(win);
}

void PrintDirListDefault(WINDOW *win){

    char **dir_list = NULL;
    int len_list = DirList(".", &dir_list);

    for(int i = 0; i < len_list; i++){
        wmove(win, i + 1, 1);
        if(dir_list[i][0] == '/'){
            wattron(win, COLOR_PAIR(3));
            wprintw(win, "%s", dir_list[i]);
            wattroff(win, COLOR_PAIR(3));
        }else{
            wattron(win, COLOR_PAIR(4));
            wprintw(win, "%s", dir_list[i]);
            wattroff(win, COLOR_PAIR(4));
        }
        
    }

    wrefresh(win);
}