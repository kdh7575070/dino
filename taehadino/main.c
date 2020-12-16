#include <ncurses.h>
#include "appearance.c"
#include "compute.c"
#include <signal.h>

void really(int signo){
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	char really;
	clear();
	mvprintw(maxY-3, maxX-15, "You Really Want to Quit?[Y/N]\n");
	while(1){
		really = getch();
		if(really=='Y'||really=='y'){
			clear();
			endwin();
			exit(0);
		}
		else if(really=='N'||really=='n') return;
	}
}

int main() {
	signal(SIGINT, really);
	signal(SIGQUIT, really);
	initscr();
	start_color();
	curs_set(FALSE);
	startMenu();
	endwin();
}
