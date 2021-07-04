#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

enum Keys{
    Keys7,
    Keys8,
    Keys9,
    KeysPlus,
    Keys4,
    Keys5,
    Keys6,
    KeysMinus,
    Keys1,
    Keys2,
    Keys3,
    KeysMult,
    KeysClear,
    Keys0,
    KeysEqual,
    KeysDiv,
    KeysDefault,
    KeysExit
};

void keyboard(int x, int y, enum Keys key);
char readkey(enum Keys *Key);



#endif //_KEYBOARD_H_