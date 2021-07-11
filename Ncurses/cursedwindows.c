#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

void SigWinch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col); 
}

int main(void){
	WINDOW *wnd;
	WINDOW *subwnd;
	
	initscr();
	signal(SIGWINCH, SigWinch);
	cbreak();
	curs_set(0);
	refresh();
	wnd = newwin(6,18,2,4);
	box(wnd,'|','-');
	subwnd =  derwin(wnd, 4, 16, 1, 1);
	wprintw(subwnd, "Hello, brave new curses world!\n");
	wrefresh(wnd);
	delwin(subwnd);
	delwin(wnd);
	move(9,0);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}
