#include <unistd.h>

#include "button.h"
#include "color.h"
#include "keyboard.h"

static char buttons[4][4] = {"789 ","456 ","123 ","c0= "};
static unsigned int count_oper = 0;

void setbutton(unsigned int number, char symbol){
    if(number < 4){
        buttons[number][3] = symbol;
    }
}

char readkey(enum Keys *Key){
    char buffer[8] = {0};
    //Дескриптор терминала STDIN_FILENO 0
    read(STDIN_FILENO, buffer, 8);

    switch (buffer[0])
    {
    case '*':
        (*Key) = (count_oper >= 3)? KeysOp3 : KeysDefault;
        break;
    case '+':
        (*Key) = (count_oper >= 1)? KeysOp1 : KeysDefault;
        break;
    case '-':
        (*Key) = (count_oper >= 2)? KeysOp2 : KeysDefault;
        break;    
    case '/':
        (*Key) = (count_oper == 4)? KeysOp4 : KeysDefault;
        break;
    case '0':
        (*Key) = Keys0;
        break;
    case '1':
        (*Key) = Keys1;
        break;
    case '2':
        (*Key) = Keys2;
        break;
    case '3':
        (*Key) = Keys3;
        break;
    case '4':
        (*Key) = Keys4;
        break;
    case '5':
        (*Key) = Keys5;
        break;
    case '6':
        (*Key) = Keys6;
        break;
    case '7':
        (*Key) = Keys7;
        break;
    case '8':
        (*Key) = Keys8;
        break;
    case '9':
        (*Key) = Keys9;
        break;
    case 'c':
        (*Key) = KeysClear;
        break;
    case '=':
        (*Key) = KeysEqual;
        break;
    case 'e':
        (*Key) = KeysExit;
        break;
    default:
        (*Key) = KeysDefault;
        return '^';
    }

    return buffer[0];
}


void keyboard(int x, int y, enum Keys key){

    for(int str = 0; str < 4; str++){
        for(int stolb = 0; stolb < 4 ; stolb++){
            if(key == (str * 4+stolb)) setfgcolor(black);
            button(x + stolb*5,y,buttons[str][stolb]);
            if(key == (str * 4+stolb)) setfgcolor(reset);
        }
        y += 3;
    }
    
}


void setcountoper(unsigned int count){
    count_oper = (count <= 4)? count : 0;
}