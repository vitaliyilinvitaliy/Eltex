#include "size_window.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

int SizeWindow(struct size_window *size){
    struct winsize sizews;

    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &sizews);

    if(sizews.ws_col < 20) return 1;

    unsigned short int horizontal = sizews.ws_col - 2;

    size->l_vertical = size->r_vertical = sizews.ws_row - 3;
    size->l_x = size->l_y = 1;
    size->r_y = 1;

    if(horizontal % 2 == 0){
        size->l_horizontal = size->r_horizontal = horizontal / 2;
        size->r_x = horizontal / 2 + 1;
    }else{
        size->l_horizontal = horizontal / 2 + 1;
        size->r_horizontal = horizontal / 2;
        size->r_x = horizontal / 2 + 2;
    }
    
}