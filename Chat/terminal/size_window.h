#ifndef _SIZE_WINDOW_H_
#define _SIZE_WINDOW_H_

struct size_window
{
    unsigned short int chat_x;
    unsigned short int chat_y;
    unsigned short int chat_horizontal;
    unsigned short int chat_vertical;

    unsigned short int input_x;
    unsigned short int input_y;
    unsigned short int input_horizontal;
    unsigned short int input_vertical;
};

struct attr_subwindow{
    unsigned short int horizontal;
    unsigned short int vertical;
};

int SizeWindow(struct size_window *);

#endif //_SIZE_WINDOW_H_