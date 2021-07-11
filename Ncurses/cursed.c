#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

void SigWinch(int signo){//обработчик сигнала SIGWINCH
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

int main(void){
	initscr();
	signal(SIGWINCH, SigWinch);
	cbreak();
	noecho();
	curs_set(0);
	box(stdscr,'*','*');
	attron(A_BOLD);
	move(5, 15);
	printw("Hello, brave new curses world!\n");
	attroff(A_BOLD);
	attron(A_BLINK);
	move(7, 16);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}
