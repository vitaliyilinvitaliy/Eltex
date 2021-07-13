#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>    

void SigWinch(int signo){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
    resizeterm(size.ws_row, size.ws_col);
}