#include <stdio.h>

#include "box.h"
#include "clearscreen.h"
#include "keyboard.h"
#include "gotoxy.h"
#include "color.h"
#include "terminal.h"
#include "display.h"
#include "displaylogic.h"



void interface(){
    enum Keys input_key = KeysDefault;
    char digit[20] = "0\0";
    char read_digit = '^';
    int light_button = -1;

    clrscr();

    rk_mytermregime(1, 1, 0, 1, 0);
    
    setfgcolor(red);
    box(0,0,22,17);
    box(2,2,2+19,2+2);
    setfgcolor(reset);

    //gotoXY(0,18);
    //printf("Last message: ");

    //int index_digit = 0;

    while (input_key != KeysExit)
    {
        display(2,2,digit);
        keyboard(2,5,input_key);
        input_key = KeysDefault;
        read_digit = readkey(&input_key);
        logic(digit,read_digit,input_key);
    }
    
    rk_mytermregime(0, 0, 1, 1, 1);
    
    //clrscr();
    gotoXY(0,22);
    printf("\n");
    
    
    
}
//gcc ../main.c interface.c clearscreen.c gotoxy.c box.c getscreensize.c button.c color.c keyboard.c display.c terminal.c -o calc


