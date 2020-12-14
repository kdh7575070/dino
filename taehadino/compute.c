#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#define MAX_QUEUE_SIZE 6

struct user {
	char name[20];
	char lastName[20];
	char age[3];
};
typedef struct {
	int x;
	int y;
	int type;
}obstacle;
obstacle Queue[MAX_QUEUE_SIZE];
obstacle *queue;
int rear, front;
char getMode;
void startEngine(int highScore, struct user firstUser);
void endGame(int score, int highScore, int diY, int diX, struct user firstUser);
void showDinasour(int diY, int diX);
void startMenu();
int computeTime(int delayTime);
int checkGame(int y, int x, int diY, int diX);
int showScoreBoard();
int isObstacle;
void qinitialize();
int isEmpty();
int isFull();
void addq(obstacle item);
void deleteq();
void updateObstacle();
void showObstacle();

void qinitialize(){
	front=rear=0;
}
int isEmpty(){
	return (front==rear);
}
int isFull(){
	return ((rear + 1) % MAX_QUEUE_SIZE == front);
}
void addq(obstacle item){
	if(isFull())
		return;
	rear++;
	rear = rear % MAX_QUEUE_SIZE;
	queue[rear] = item;
}
void deleteq(){
	front = (front + 1) % MAX_QUEUE_SIZE;
}
void updateObstacle(){
	int i = front;
	for(;i!=rear;){
		i = (i+1) % MAX_QUEUE_SIZE;
		clearCactus1(queue[i].y,queue[i].x);
		queue[i].x -= 7;
		if(queue[i].x<0){
			clearCactus1(queue[i].y,queue[i].x);
			deleteq();
		}
	}
}
void showObstacle(){
	int i = front;
	for(;i!=rear;){
		i = (i+1) % MAX_QUEUE_SIZE;
		if(queue[i].type == 0)
			cactus1(queue[i].y, queue[i].x);
		else if(queue[i].type == 1)
			cactus2(queue[i].y, queue[i].x);
		else
			cactus3(queue[i].y, queue[i].x);
	}
}
// Check if the game is going to be finished in this turn of loop
int checkGame(int y, int x, int diY, int diX) {
	if (diY == y) {
		if (abs((diX+14)-x) <= 3) {
			return 0;
		}
	}
	return 1;
}

int showScoreBoard()
{
	int highScore, scores;
	char name[100];
	int count=0;
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	 // Read high score from file
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");

	mvprintw(maxY-5, maxX-15, "          << Score Board! >>\n");
	mvprintw(maxY-3, maxX-15, "%s %30s\n", "Score", "name");
	fscanf(highScoreFile, "%d %s", &scores, name);
	while(!feof(highScoreFile)){
		if(count==0) highScore = scores;
		mvprintw(maxY+count-1, maxX-15, "%4d %30s", scores, name);
		fscanf(highScoreFile, "%d %s", &scores, name);
		count++;
		if(count==10) break;
	}
	fclose(highScoreFile);
	getstr(name);
	return highScore;
}

// Make game faster
int computeTime(int delayTime) {
	if (delayTime >= 250000) {
		delayTime -= 10000;
	}
	else if (delayTime >= 200000) {
		delayTime -= 5000;
	}
	else {
		delayTime -= 10;
	}
	return delayTime;
}

// The very first menu
void startMenu() {
	struct user firstUser;
	int highScore, scores;
	
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	showTrex(maxY, maxX);
	attroff(COLOR_PAIR(3));
    // Get information from user
	mvprintw(maxY+2, maxX-24, "Write inputs and press Enter to start Game.");
    mvprintw(maxY+3, maxX-22, "In case you wanna quit, put CTRL+C !");
	mvprintw(maxY+4, maxX-20, "You can jump with space key!");
	mvprintw(maxY+6, maxX-12, "Name: ");
	getstr(firstUser.name);
	mvprintw(maxY+7, maxX-12, "Last name: ");
	getstr(firstUser.lastName);
	mvprintw(maxY+8, maxX-12, "Age: ");
	getstr(firstUser.age);
	noecho();

	clear();
	highScore = showScoreBoard();
	
	startEngine(highScore, firstUser);
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

// Finishing function - 헷갈리지 말기 y축이 먼저, 그다음이 x축방향임
void endGame(int score, int highScore, int diY, int diX, struct user firstUser) {
	nodelay(stdscr, FALSE);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	int scores;
	char name[100];
	char write[110];
	char writing[10][110];
	int iswrite=0;
    // Save high score
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");
	int count=0;
	fscanf(highScoreFile, "%d %s", &scores, name);
	while(!feof(highScoreFile)){
		if(scores<score&&iswrite==0){
			if(!strcmp(firstUser.name,""))strcpy(firstUser.name, "NULL");
			sprintf(write, "%d %s\n", score, firstUser.name);
			strcpy(writing[count++], write);
			iswrite=1;
			if(count==10) break;
		}
		sprintf(write, "%d %s\n", scores, name);
		strcpy(writing[count++], write);
		if(count==10) break;
		fscanf(highScoreFile, "%d %s", &scores, name);
	}
	fclose(highScoreFile);
	highScoreFile = fopen("./highScore.txt", "w");
	for(int i=0;i<count;i++) fprintf(highScoreFile, "%s", writing[i]);
	fclose(highScoreFile);

	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	attron(COLOR_PAIR(2));
	showLoss(maxY, maxX);
	char keyToExit = getch();
    // Exit or reset game
	if (keyToExit == 'r' || keyToExit == 'R') {
		attroff(COLOR_PAIR(2));
		startEngine(highScore, firstUser);
	}
	else if (keyToExit == 'q' || keyToExit == 'Q') {
		clear();
		showScoreBoard();
		return;
	}
	else {
		endGame(score, highScore, diY, diX, firstUser);
	}
}

// The main engine!
void startEngine(int highScore, struct user firstUser)
{
	srand(time(NULL));
	int x, y, diX = 10, score = 0, delayTime = 300000, gameStatus = 1, cactusNum = 0;
	int maxX = getmaxx(stdscr);
	x = maxX - 20;
	y = getmaxy(stdscr) - 6;
	int diY = y;
	char userInput;
	clear();
	nodelay(stdscr, TRUE);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	bool isBottom = true;
	bool isJumping = false;
	bool beforeInput_jump = false;

	obstacle cactus;
	queue = Queue; // obstacle queue
	qinitialize(); // init queue
	cactus.x = x;
	cactus.y = y; 
	cactus.type = cactusNum;
	addq(cactus);  // add cactus before while

	while (gameStatus == 1)
	{
		userInput = getch();
		tcflush(0, TCIFLUSH);

		// Show day or night
		if (((score / 100)) % 2)
		{ //100의자리대가짝수일때
			clear();
			attron(COLOR_PAIR(3));
			moon(10, (maxX / 2) - 10);
		}
		else
		{
			attron(COLOR_PAIR(1));
			sun(10, (maxX / 2) - 10);
		}

		score++;
		// Show informations
		mvprintw(1, 6, "%s %s", firstUser.name, firstUser.lastName);
		mvprintw(1, getmaxx(stdscr) - 9, "%d:%d", highScore, score);

		// ----------
		box(stdscr, ACS_VLINE, ACS_HLINE);

		//for clearing screen
		clearDinasourUp(diY, diX);
		isObstacle = rand() % 10; 		// create obstacle or not
		if( isObstacle == 1 ){	   		// probability of creating obstacle: 10%
			cactusNum = rand() % 3; 	// decide the type of cactus
			cactus.x = getmaxx(stdscr)-20; // initial x-axis position of cactus
			cactus.y = y;			// initial y-axis position of cactus
			cactus.type = cactusNum;	// type of cactus
			addq(cactus);
		}
		// if input is equal to ' ' then jump
		if (userInput == ' ' && isBottom && !isJumping)
		{
			isJumping = true;
			isBottom = false;
			beforeInput_jump = true;
		}

		if (isJumping)
		{
			diY -= 7;
		}
		else if (beforeInput_jump)
		{
			beforeInput_jump = false;
		}
		else
		{
			diY += 7;
		}

		if (diY >= y)
		{
			diY = y;
			isBottom = true;
		}

		if (isJumping)
		{
			clearDinasourDown(diY, diX);
			isJumping = false;
		}
		else clearDinasourUp(diY, diX);
		if (diY <= 7)
		{
			isJumping = false;
		}

		obstacle first = queue[ (front+1)%MAX_QUEUE_SIZE ];   // closest obstacle from dinosaur
		showObstacle();					// show all cactus in queue

		gameStatus = checkGame(first.y, first.x, diY, diX);
		// Bring back dinosaur

		mvhline(y + 1, 1, '-', getmaxx(stdscr) - 3);
		updateObstacle();
		if (userInput == ' ') {
			diY -= 7;
		}
		/* show character you chose*/
		switch(getMode){
			case 'a':
				showDinasour(diY, diX);
				break;
			case 'b':
				showPeople(diY, diX);
				break;
		}
		
		refresh();
		// clearCactus1(y, x);
		// refresh();
		usleep(delayTime);
		x -= 7;
		delayTime = computeTime(delayTime);
		userInput = 'q';
	}
	// When code reaches here, means that user is loss
	endGame(score, highScore, diY, diX, firstUser);
	attroff(COLOR_PAIR(1));
}
