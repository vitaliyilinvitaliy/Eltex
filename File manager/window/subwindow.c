#include "../terminal/size_window.h"
#include "../directory/dir_list.h"
#include "../directory/print_dir_list.h"
#include "../window/color_string.h"
#include "../window/clear_subwindow.h"
#include "../process/start_process.h"
#include "subwindow.h"
#include "../terminal/term.h"

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int Subwindow(WINDOW *win, char *directory, struct attr_subwindow atsubw){
    char **spis = NULL;
    int len_list = DirList(directory, &spis);
    int len_dir = 0;
    int ch = 0, i = 0;
    int index_str = 0;
    bool flag_break = FALSE;

    char last_dir[256] = "/.";
    int start_printw = 0;

    wattron(win,COLOR_PAIR(1));
    box(win,0,0);
    wrefresh(win);

    ColorString(win,spis[index_str],index_str,ON_STR);

    while ((ch = wgetch(win)) != '\t')
    {
        switch (ch)
        {
        case KEY_UP:
            if(index_str == 0) break;
            ColorString(win, spis[index_str], index_str,OFF_STR);
            index_str--;
            ColorString(win, spis[index_str], index_str,ON_STR);
            break;
        
        case KEY_DOWN:
            if(index_str == len_list - 1) break;
            ColorString(win, spis[index_str], index_str, OFF_STR);
            index_str++;
            ColorString(win, spis[index_str], index_str, ON_STR);
            break;
        case '\n':
            if(spis[index_str][0] == '/'){
                
                strcat(directory,spis[index_str]);//stack smash!!!!!
                
                chdir(directory);
                getcwd(directory, 256);

                len_dir = strlen(directory);
                wmove(win,0,atsubw.horizontal/4);

                if(len_dir > (atsubw.horizontal/2)){
                    
                    start_printw = len_dir - (atsubw.horizontal/2);
                    wprintw(win,"...");
                    
                    for(i = start_printw; i < len_dir; i++){
                        wprintw(win,"%c",directory[i]);
                    }
                }else{
                    wprintw(win,"%s          ",directory);
                }

                for(i = 0; i < len_list; i++){
                    free(spis[i]);
                }

                free(spis);
                spis = NULL;
                ClearSbw(win, atsubw.horizontal, atsubw.vertical);
                
                len_list = DirList(directory, &spis);
                PrintDirList(win, spis, len_list);

                index_str = 0;
                ColorString(win,spis[index_str],index_str,ON_STR);
            }else{
                if(TermStoreDefault() == 0){
                    StartProcess(win, directory, spis[index_str]);
                    ch = REFRESH_WIN;
                    flag_break = TRUE;
                }                
            }
            break;
        case KEY_F(1):
            flag_break = TRUE;
            ch = KEY_F(1);
            break;
        case KEY_F(5):
            flag_break = TRUE;
            ch = KEY_F(1);
            break;
        default:
            break;
        }

        if(flag_break){
            break;
        }
    }

    wattroff(win,COLOR_PAIR(1));
    box(win,0,0);
    ColorString(win, spis[index_str], index_str, OFF_STR);
    wrefresh(win);

    return ch;
}