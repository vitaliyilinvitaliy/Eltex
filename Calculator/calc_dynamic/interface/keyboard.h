#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

enum Keys{
    Keys7,
    Keys8,
    Keys9,
    KeysOp1,
    Keys4,
    Keys5,
    Keys6,
    KeysOp2,
    Keys1,
    Keys2,
    Keys3,
    KeysOp3,
    KeysClear,
    Keys0,
    KeysEqual,
    KeysOp4,
    KeysDefault,
    KeysExit
};

void keyboard(int x, int y, enum Keys key);
char readkey(enum Keys *Key);
void setbutton(unsigned int number, char symbol);
void setcountoper(unsigned int count);

#endif //_KEYBOARD_H_