#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>

void sig_winch_mouse(int signo){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    
    nodelay(stdscr, 1);

    while(wgetch(stdscr) != ERR);

    nodelay(stdscr, 0);
}