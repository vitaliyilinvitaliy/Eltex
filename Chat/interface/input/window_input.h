#ifndef _WINDOW_INPUT_H_
#define _WINDOW_INPUT_H_

#include <ncurses.h>

int InitInput(int, int, int, int);
int Input(WINDOW *, struct my_parameters *);

#endif //_WINDOW_INPUT_H_