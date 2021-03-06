#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
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

void startEngine(int highScore, struct user firstUser);
int computePrize(int score, int usedPrize);
void endGame(int score, int highScore, int diY, int diX, struct user firstUser);
void showDinasour(int diY, int diX);
void startMenu();
int computeTime(int delayTime);
int checkGame(int y, int x, int diY, int diX);

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
		if (abs((diX+14)-x) <= 4) {
			return 0;
		}
	}
	return 1;
}

// Make game faster
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
	fscanf(highScoreFile, "%d", &highScore);
	fclose(highScoreFile);
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	showTrex(maxY, maxX);
	attroff(COLOR_PAIR(3));
    // Get information from user
	mvprintw(maxY+1, maxX-28, "Write inputs and press Enter to start Game.");
    	mvprintw(maxY+2, maxX-26, "When you had prize, fire it with 'k' key!");
	mvprintw(maxY+3, maxX-21, "You can jump with space key!");
	mvprintw(maxY+4, maxX-15, "Name: ");
	getstr(firstUser.name);
	mvprintw(maxY+5, maxX-15, "Last name: ");
	getstr(firstUser.lastName);
	mvprintw(maxY+6, maxX-15, "Age: ");
	getstr(firstUser.age);
	noecho();
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
    // Save high score
	if (score > highScore) {
		highScore = score;
		FILE *highScoreFile;
		highScoreFile = fopen("./highScore.txt", "w");
		fprintf(highScoreFile, "%d\n", highScore);
		fclose(highScoreFile);
	}
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	attron(COLOR_PAIR(2));
	showLoss(maxY, maxX);
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
	int x, y, diX=10, prize=0, usedPrize=0, score=0, delayTime = 300000, gameStatus=1, cactusNum=0;
	int maxX=getmaxx(stdscr);
	x = maxX-20;
	y = getmaxy(stdscr)-6;
	int diY = y;
	char userInput;
	obstacle cactus;
	queue = Queue; // obstacle queue
	qinitialize(); // init queue
	cactus.x = x;
	cactus.y = y; 
	cactus.type = cactusNum;
	addq(cactus);  // add cactus before while
    	
    	clear();
	nodelay(stdscr, TRUE);
  	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	while (gameStatus == 1) {
		userInput = getch();
		tcflush(0, TCIFLUSH);
		// Show day or night
		if (((score/100))%2){//100의자리대가짝수일때
            		clear();
			attron(COLOR_PAIR(3));
			moon(10, (maxX/2)-10);			
		}
		else {
			attron(COLOR_PAIR(1));
			sun(10, (maxX/2)-10);			
		}

		score++;
        // Show informations
		mvprintw(1, 6, "%s %s", firstUser.name, firstUser.lastName);
		mvprintw(1, getmaxx(stdscr)-9, "%d:%d", highScore, score);

		// ----------
		box(stdscr, ACS_VLINE, ACS_HLINE);
		//for clearing screen
		clearDinasourUp(diY, diX);
		
	/* random obstacle */
		isObstacle = rand() % 10; 		// create obstacle or not
		if( isObstacle == 1 ){	   		// probability of creating obstacle: 10%
			cactusNum = rand() % 3; 	// decide the type of cactus
			cactus.x = getmaxx(stdscr)-20; // initial x-axis position of cactus
			cactus.y = y;			// initial y-axis position of cactus
			cactus.type = cactusNum;	// type of cactus
			addq(cactus);			// add cactus to queue
		}
		
        // if input is equal to ' ' then jump
		if (userInput == ' ') {
			diY -= 7;
		}
		showDinasour(diY, diX);
		if (userInput == ' ') {
			clearDinasourDown(diY, diX);		
		}
		obstacle first = queue[ (front+1)%MAX_QUEUE_SIZE ];   // closest obstacle from dinosaur
		showObstacle();					// show all cactus in queue
		
		gameStatus = checkGame(first.y, first.x, diY, diX);

	       // Bring back dinosaur
		if (userInput == ' ') {
			diY += 7;
		}
		mvhline(y+1, 1, '-', getmaxx(stdscr)-3);
		updateObstacle();					// move all cactus to left
		
		refresh();
		usleep(delayTime);
		delayTime = computeTime(delayTime);
		userInput = 'q';
	}
    // When code reaches here, means that user is loss
	endGame(score, highScore, diY, diX, firstUser);
	attroff(COLOR_PAIR(1));
}
