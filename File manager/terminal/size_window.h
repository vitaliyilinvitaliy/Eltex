#ifndef _SIZE_WINDOW_H_
#define _SIZE_WINDOW_H_

struct size_window
{
    unsigned short int l_x;
    unsigned short int l_y;
    unsigned short int l_horizontal;
    unsigned short int l_vertical;

    unsigned short int r_x;
    unsigned short int r_y;
    unsigned short int r_horizontal;
    unsigned short int r_vertical;
};

struct attr_subwindow{
    unsigned short int horizontal;
    unsigned short int vertical;
};

int SizeWindow(struct size_window *);

#endif //_SIZE_WINDOW_H_