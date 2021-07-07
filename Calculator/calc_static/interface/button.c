#include <stdio.h>

#include "box.h"
#include "gotoxy.h"

void button(int x, int y, char symbol){
    box(x,y,x+4,y+2);

    gotoXY(x+2,y+1);

    printf("%c",symbol);
}