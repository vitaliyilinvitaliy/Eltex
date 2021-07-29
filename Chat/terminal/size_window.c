#include "size_window.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

int SizeWindow(struct size_window *size){
    struct winsize sizews;

    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &sizews);

    if(sizews.ws_col < 20 || sizews.ws_row < 20) return 1;

    (*size).chat_horizontal = ((sizews.ws_col - 2) / 4) * 3;
    (*size).chat_vertical = (sizews.ws_row / 4) * 3;
    (*size).chat_x = 1;
    (*size).chat_y = 1;
    
    (*size).input_horizontal = sizews.ws_col - 2;
    (*size).input_vertical = sizews.ws_row  - ((sizews.ws_row / 4) * 3) - (*size).chat_y - 2;
    (*size).input_x = 1;
    (*size).input_y = (sizews.ws_row / 4) * 3 + (*size).chat_y;

    return 0;
}