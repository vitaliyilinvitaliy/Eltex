#ifndef _SUBWINDOW_H_
#define _SUBWINDOW_H_

#include "../terminal/size_window.h"

#include <curses.h>

#define REFRESH_WIN -2

int Subwindow(WINDOW *, char *, struct attr_subwindow);

#endif //_SUBWINDOW_H_