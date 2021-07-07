#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gotoxy.h"
#include "color.h"


void display(int x, int y, char* str){
    gotoXY(x+1,y+1);

    size_t size_str = strlen(str);

    if(size_str <= 18){
         setfgcolor(green);
        for(int i = 0; i < (18-size_str);i++){
            printf("^");
        }
        setfgcolor(reset);

        printf("%s",str);
    }
}