#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <signal.h>
#include <curses.h>
#include <string.h>

#define MAX_LEN 15
#define RIGHT_PASSWORD "Vitalik"

void SigWinch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void GetPassword(WINDOW *win, char *password, int max_len){
	int i = 0;
	int ch;
	while (((ch = wgetch(win)) != 10) && (i < max_len-1)) {
		if (ch == KEY_BACKSPACE) {
			int x, y;
			if (i==0) continue;
			getyx(win, y, x);
			mvwaddch(win, y, x-1, ' ');
			wrefresh(win);
			wmove(win, y, x-1);
			i--;
			continue;
		}
		int x, y;
		getyx(win, y, x);
		wmove(win, y, x - 1);
		wechochar(win, '*');
		wmove(win, y, x);
		password[i++] = ch;
	}
	password[i] = 0;
	wechochar(win, '\n');
}


int main(){
	WINDOW * wnd;
	char password[MAX_LEN + 1];
	initscr();
	signal(SIGWINCH, SigWinch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(5, 23, 2, 2);
	wbkgd(wnd, COLOR_PAIR(1));
	wattron(wnd, A_BOLD);

	keypad(wnd, TRUE);
	wprintw(wnd, "Enter password...\n");
	GetPassword(wnd, password, MAX_LEN);
	wattron(wnd, A_BLINK);
	if(strcmp(password, RIGHT_PASSWORD) == 0){
		wprintw(wnd, "ACCESS GRANTED!");
	}else{
		wprintw(wnd, "ACCESS DENIED!");
	}


	wrefresh(wnd);
	delwin(wnd);
	curs_set(FALSE);
	move(8, 4);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}

