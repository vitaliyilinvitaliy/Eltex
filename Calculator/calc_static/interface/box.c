#include <stdio.h>

#include "gotoxy.h"

int printA(char *str)
{
    printf("\E(0%s\E(B", str);
}

int box(int x1, int y1, int x2, int y2)
{
    //mt_setbgcolor(black);
    if (x1 == 0)
        x1 = 1;
    for (int CoordX = x1 + 1; CoordX < x2; CoordX++)
    {
        gotoXY(CoordX, y1);
        printA("r");
    }
    for (int CoordY = y1 + 1; CoordY < y2; CoordY++)
    {
        gotoXY(x1, CoordY);
        printA("x");
    }

    for (int CoordX = x1 + 1; CoordX < x2; CoordX++)
    {
        gotoXY(CoordX, y2);
        printA("r");
    }
    for (int CoordY = y1 + 1; CoordY < y2; CoordY++)
    {
        gotoXY(x2, CoordY);
        printA("x");
    }
    gotoXY(x1, y1);
    printA("l");
    gotoXY(x1, y2);
    printA("m");
    gotoXY(x2, y1);
    printA("k");
    gotoXY(x2, y2);
    printA("j");
    //mt_setbgcolor(black);
}