#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <termio.h>

struct user {
	char name[20];
	char age[3];
};

void startEngine(int highScore, struct user firstUser);
int computePrize(int score, int usedPrize);
void endGame(int score, int highScore, int diY, int diX, struct user firstUser);
void showDinasour(int diY, int diX);
void startMenu();
int computeTime(int delayTime); //게임 속도를 점점 빠르게 만들어 줌
int checkGame(int y, int x, int diY, int diX);

// Check if the game is going to be finished in this turn of loop
int checkGame(int y, int x, int diY, int diX) {
	if (diY == y) {
		if (abs((diX+14)-x) <= 4) {
			return 0;
		}
	}
	return 1;
}

// Make game faster(게임 속도를 더 빠르게 만들어주기)
int computeTime(int delayTime) {
	if (delayTime >= 250000) {
		delayTime -= 900;
	}
	else if (delayTime >= 200000) {
		delayTime -= 600;
	}
	else {
		delayTime -= 200;
	}
	return delayTime;
}

// The very first menu
void startMenu() {
	struct user firstUser;
	int highScore;
    // Read high score from file
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");
	fscanf(highScoreFile, "%d", &highScore);//오른쪽 최상단에 최고점수:현재점수 표시가 됨
	fclose(highScoreFile);
	int maxX = getmaxx(stdscr)/2;//초기화면(메뉴, 이름 등록) 위치 설정
	int maxY = getmaxy(stdscr)/2;
	init_pair(3,COLOR_GREEN,COLOR_BLACK);//trex글자 색 설정
	attron(COLOR_PAIR(3));//글자에 특수효과를 줌
	showTrex(maxY, maxX);
	attroff(COLOR_PAIR(3));
    // Get information from user
	mvprintw(maxY+1, maxX-28, "Write inputs and press Enter to start Game.");
    mvprintw(maxY+2, maxX-26, "When you had prize, fire it with 'k' key!");
	mvprintw(maxY+3, maxX-21, "You can jump with space key!");
	mvprintw(maxY+4, maxX-15, "Name: ");
	getstr(firstUser.name);//이름
	mvprintw(maxY+6, maxX-15, "Age: ");
	getstr(firstUser.age);//나이
	noecho();
	startEngine(highScore, firstUser);//게임 시작
}

// Which dinosaur should be printed
void showDinasour(int diY, int diX) {
	static int counter = 0;
	if (counter == 0) {
		dinasour1(diY, diX);
		counter++;
	}
	else {
		dinasour2(diY, diX);
		counter--;
	}
}

// Finishing function
void endGame(int score, int highScore, int diY, int diX, struct user firstUser) {
	nodelay(stdscr, FALSE);
	init_pair(2,COLOR_RED,COLOR_BLACK);
    // Save high score
	if (score > highScore) {
		highScore = score;
		FILE *highScoreFile;
		highScoreFile = fopen("./highScore.txt", "w");
		fprintf(highScoreFile, "%d", highScore);
		fclose(highScoreFile);
	}
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	attron(COLOR_PAIR(2));
	showLoss(maxY, maxX);
	mvprintw(diY-4, diX, "          X-X ");
	mvprintw(diY, diX, "      ||");
	char keyToExit = getch();
    // Exit or reset game
	if (keyToExit == 'r') {
		attroff(COLOR_PAIR(2));
		startEngine(highScore, firstUser);
	}
	else if (keyToExit == 'q') {
		return;
	}
	else {
		endGame(score, highScore, diY, diX, firstUser);
	}
}

// Give user the arrow
int computePrize(int score, int usedPrize) {
	if (score >= 20 && score <= 40 && usedPrize == 0) {
		return 1;
	}
	else if (score >= 60 && score <= 80 && usedPrize <= 1) {
		return 1;
	}
	else if (score >= 100 && score <= 120 && usedPrize <= 2) {
		return 1;
	}	
	return 0;
}

// The main engine!
void startEngine(int highScore, struct user firstUser) {
    srand(time(NULL));
	int x, y, diX=5, prize=0, usedPrize=0, score=0, delayTime = 300000, gameStatus=1, cactusNum=0;
	int maxX=getmaxx(stdscr);
	x = maxX-20;
	y = getmaxy(stdscr)-6;
	int diY = y;
	int arrowX=(diX+15), arrowY=(diY-3);//arrow??
	char userInput, inputc;
    bool fire=FALSE;
    clear();
	nodelay(stdscr, TRUE);
  	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	while (gameStatus == 1) {
		inputc = getch();
		if(inputc==userInput) userInput='n';
		else userInput=inputc;
		tcflush(0, TCIFLUSH);
		// Show day or night
		if ((score >= 20 && score <= 40) || (score >= 70 && score <= 90) || (score >= 120 && score <= 150)) {//score따라 배경 색을 변하도록
            clear();
			attron(COLOR_PAIR(4));
			moon(10, (maxX/2)-10);			//달도 나오도록
		}
		else {
			attron(COLOR_PAIR(1));
			sun(10, (maxX/2)-10);			
		}
		// clear arrow
		if (fire) {//arrow?
			mvprintw(arrowY, arrowX-2, " ");
		}

		score++;
        // Show informations
		mvprintw(1, 6, "%s %s", firstUser.name, firstUser.age);
		mvprintw(1, getmaxx(stdscr)-9, "%d:%d", highScore, score);
		// Use prize to destroy cactus
		prize = computePrize(score, usedPrize);
		mvprintw(3, 6, "Prize: %d", prize);
		if (prize == 1) {//prize가 뭐지?
			if (userInput == 'k') {//k 입력 시 usedPrize
				usedPrize++;
				fire = TRUE;
			}
		}
		if (fire) {
			mvprintw(arrowY, arrowX, "*");
			arrowX += 2;
		}
		if ((x+4)-arrowX <= 1 && fire) {
			clearCactus1(y, x-1);
			mvprintw(arrowY, arrowX-2, " ");
			x = getmaxx(stdscr)-20;
			fire = FALSE;
			arrowX = diX+15;
		}
		// ----------
		box(stdscr, ACS_VLINE, ACS_HLINE);
		//for clearing screen
		clearDinasourUp(diY, diX);
		if (x <= 7) {
			x = getmaxx(stdscr)-20;
            cactusNum = rand() % 2;
		}
        // if input is equal to ' ' then jump
		if (userInput == ' ') {
			diY -= 7;
		}
		showDinasour(diY, diX);
		if (userInput == ' ') {
			clearDinasourDown(diY, diX);		
		}
		if (x-diX <= 7) {
			x -= 10;
		}
        if (cactusNum == 0) {
        	cactus1(y, x);
		}
		else {
			cactus2(y, x);
		}
		if (x-diX <= 7) {
			x += 10;
		}
		gameStatus = checkGame(y, x, diY, diX);
        // Bring back dinosaur
		if (userInput == ' ') {
			diY += 7;
		}
		mvhline(y+1, 1, '-', getmaxx(stdscr)-3);
        refresh();
        clearCactus1(y, x);
		refresh();
        usleep(delayTime);
        x -= 7;
        delayTime = computeTime(delayTime);
		userInput = 'q';
	}
    // When code reaches here, means that user is loss
	endGame(score, highScore, diY, diX, firstUser);
	attroff(COLOR_PAIR(1));
}