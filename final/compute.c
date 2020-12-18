#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <termio.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include "set_ticker.c"
#define MAX_QUEUE_SIZE 6

struct user
{
	char name[20];
	char lastName[20];
	char age[3];
};
typedef struct
{
	int x;
	int y;
	int type;
} obstacle;
obstacle Queue[MAX_QUEUE_SIZE];
obstacle *queue;

void startEngine();
void endGame(int score, int diY, int diX);
void showDinasour(int diY, int diX);
void startMenu();
int computeTime(int delayTime);
int checkGame(int y, int x, int diY, int diX);
void show();
int set_ticker(int);
int showScoreBoard();
int isObstacle;
void qinitialize();
int isEmpty();
int isFull();
void addq(obstacle item);
void deleteq();
void updateObstacle();
void showObstacle();

int x, y, diX = 5, score = 0, delayTime = 300, gameStatus = 1, cactusNum = 0;
int maxX, diY;
bool isBottom = true;
bool isJumping = false;
bool beforeInput_jump = false;
char userInput;
struct user firstUser;
int highScore;
int rear, front;
char getMode;
obstacle cactus;
/*
on_input(), on_alarm(), enable_kbd_signals() 는 ch7. bound_async.c 에서 가져옴
전체적인 방식은 bound_async.c와 유사합니다.
startEngine(), startMenu()에 매개변수 필요없음. 전역변수로 대체.
show() : 화면에 보여지는 함수. alarm이 켜질때 마다 호출됨.
startMenu -> startEngine(전역변수 초기값 설정, signal설정 ...) 이후 signal handler로 화면출력 및 input을 받습니다.
타이밍이 안 맞아서 조정했는데 완벽하지는 않습니다..
속도조절은 score가 x점일때 속도를 y로 설정하는 방식으로 바꿨습니다.
일단 돌아가는거는 확인했는데 타이밍이나 기타 세부사항은 확인하지 못 했습니다. 
다른 분들께서 돌려보시고 수정해주시면 감사하겠습니다!
*/
void on_input(int signum)
{
	int c = getch(); /* grab the char */
	//userInput = c;
	userInput = c;
}

void on_alarm(int signum)
{
	signal(SIGALRM, on_alarm); /* reset, just in case	*/
	show();
	userInput = 'q';
}

void enable_kbd_signals()
{
	int fd_flags;

	fcntl(0, F_SETOWN, getpid());		  /*set io signal to current pid*/
	fd_flags = fcntl(0, F_GETFL);		  /*get status of the file*/
	fcntl(0, F_SETFL, (fd_flags | O_ASYNC)); /*set status to tty with O_ASYNC*/
}

int showScoreBoard()
{
	int highScore, scores;
	char name[100];
	int count = 0;
	int maxX = getmaxx(stdscr) / 2;
	int maxY = getmaxy(stdscr) / 2;
	// Read high score from file
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");

	mvprintw(maxY - 5, maxX - 15, "          << Score Board! >>\n");
	mvprintw(maxY - 3, maxX - 15, "%s %30s\n", "Score", "name");
	fscanf(highScoreFile, "%d %s", &scores, name);
	while (!feof(highScoreFile))
	{
		if (count == 0)
			highScore = scores;
		mvprintw(maxY + count - 1, maxX - 15, "%4d %30s", scores, name);
		fscanf(highScoreFile, "%d %s", &scores, name);
		count++;
		if (count == 10)
			break;
	}
	fclose(highScoreFile);
	getstr(name);
	return highScore;
}

void qinitialize()
{
	front = rear = 0;
}
int isEmpty()
{
	return (front == rear);
}
int isFull()
{
	return ((rear + 1) % MAX_QUEUE_SIZE == front);
}
void addq(obstacle item)
{
	if (isFull())
		return;
	rear++;
	rear = rear % MAX_QUEUE_SIZE;
	queue[rear] = item;
}
void deleteq()
{
	front = (front + 1) % MAX_QUEUE_SIZE;
}
void updateObstacle()
{
	int i = front;
	for (; i != rear;)
	{
		i = (i + 1) % MAX_QUEUE_SIZE;
		clearCactus1(queue[i].y, queue[i].x);
		queue[i].x -= 7;
		if (queue[i].x < 0)
		{
			clearCactus1(queue[i].y, queue[i].x);
			deleteq();
		}
	}
}
void showObstacle()
{
	int i = front;
	for (; i != rear;)
	{
		i = (i + 1) % MAX_QUEUE_SIZE;
		if (queue[i].type == 0)
			cactus1(queue[i].y, queue[i].x);
		else if (queue[i].type == 1)
			cactus2(queue[i].y, queue[i].x);
		else
			cactus3(queue[i].y, queue[i].x);
	}
}

// Collison check
int checkGame(int y, int x, int diY, int diX)
{
	if (diY == y)
	{
		if (abs((diX + 14) - x) <= 2)
		{
			return 0;
		}
	}
	return 1;
}

// Make game faster
int computeTime(int delayTime)
{
	if (score >= 100)
	{
		delayTime = 280;
	}
	else if (score >= 200)
	{
		delayTime = 260;
	}

	return delayTime;
}

// The very first menu
void startMenu()
{
	int maxX = getmaxx(stdscr) / 2;
	int maxY = getmaxy(stdscr) / 2;
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	showTeam1(maxY, maxX);
	attroff(COLOR_PAIR(3));
	
	// Get information from user
	mvprintw(maxY + 2, maxX - 24, "Write inputs and press Enter to start Game.");
	mvprintw(maxY + 3, maxX - 22, "In case you wanna quit, put CTRL+C !");
	mvprintw(maxY + 4, maxX - 20, "You can jump with space key!");
	mvprintw(maxY + 6, maxX - 12, "Name: ");
	getstr(firstUser.name);
	mvprintw(maxY + 7, maxX - 12, "Last name: ");
	getstr(firstUser.lastName);
	mvprintw(maxY + 8, maxX - 12, "Age: ");
	getstr(firstUser.age);
	mvprintw(maxY + 9, maxX - 12,  "Select mode [ a ] : dino (default)");
	mvprintw(maxY + 10, maxX - 12, "Select mode [ b ] : human");
	mvprintw(maxY + 11, maxX - 12, "Select mode [ c ] : alpaca");
	mvprintw(maxY + 12, maxX - 12, "Select mode [ d ] : amongus");
	getMode = getch();
	noecho();

	clear();
	highScore = showScoreBoard();

	startEngine();
}

// Which dinosaur should be printed
void showDinasour(int diY, int diX)
{
	static int counter = 0;
	if (counter == 0)
	{
		dinasour1(diY, diX);
		counter++;
	}
	else
	{
		dinasour2(diY, diX);
		counter--;
	}
}
void showPeople(int diY, int diX)
{
	static int counter = 0;
	if (counter == 0)
	{
		people1(diY, diX);
		counter++;
	}
	else
	{
		people2(diY, diX);
		counter--;
	}
}
void showAmongus(int diY, int diX)
{
	static int counter = 0;
	if (counter == 0)
	{
		amongus1(diY, diX);
		counter++;
	}
	else
	{
		amongus2(diY, diX);
		counter--;
	}
}
void showAlphaca(int diY, int diX)
{
	static int counter = 0;
	if (counter == 0)
	{
		alphaca1(diY, diX);
		counter++;
	}
	else
	{
		alphaca2(diY, diX);
		counter--;
	}
}
// Finishing function - 헷갈리지 말기 y축이 먼저, 그다음이 x축방향임
void endGame(int score, int diY, int diX)
{
	nodelay(stdscr, FALSE);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	int scores;
	char name[100];
	char write[110];
	char writing[10][110];
	int iswrite = 0;
	
	// Save high score
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");
	int count = 0;
	fscanf(highScoreFile, "%d %s", &scores, name);
	while (!feof(highScoreFile))
	{
		if (scores < score && iswrite == 0)
		{
			if (!strcmp(firstUser.name, ""))
				strcpy(firstUser.name, "NULL");
			sprintf(write, "%d %s\n", score, firstUser.name);
			strcpy(writing[count++], write);
			iswrite = 1;
			if (count == 10)
				break;
		}
		sprintf(write, "%d %s\n", scores, name);
		strcpy(writing[count++], write);
		if (count == 10)
			break;
		fscanf(highScoreFile, "%d %s", &scores, name);
	}
	fclose(highScoreFile);
	highScoreFile = fopen("./highScore.txt", "w");
	for (int i = 0; i < count; i++)
		fprintf(highScoreFile, "%s", writing[i]);
	fclose(highScoreFile);

	maxX = getmaxx(stdscr) / 2;
	int maxY = getmaxy(stdscr) / 2;
	attron(COLOR_PAIR(2));
	showLoss(maxY, maxX);
	char keyToExit = getch();
	// Exit or reset game
	if (keyToExit == 'r' || keyToExit == 'R')
	{
		attroff(COLOR_PAIR(2));
		//startEngine(highScore, firstUser);
		startEngine();
	}
	else if (keyToExit == 'q' || keyToExit == 'Q')
	{
		clear();
		showScoreBoard();
		return;
	}
	else
	{
		endGame(score, diY, diX);
	}
}

// The main engine!
void startEngine()
{
	srand(time(NULL));
	clear();
	nodelay(stdscr, TRUE);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);

	isBottom = true;
	isJumping = false;
	beforeInput_jump = false;
	//gameStatus = 1;
	score = 0;
	delayTime = 300;

	maxX = getmaxx(stdscr);
	x = maxX - 20;
	y = getmaxy(stdscr) - 6;
	diY = y;
	obstacle cactus;
	queue = Queue; // obstacle queue
	qinitialize(); // init queue
	cactus.x = x;
	cactus.y = y;
	cactus.type = cactusNum;
	addq(cactus); // add cactus before while

	signal(SIGIO, on_input);	 /* install a handler        */
	enable_kbd_signals();		 /* turn on kbd signals      */
	signal(SIGALRM, on_alarm); 	 /* install alarm handler    */
	set_ticker(delayTime);		 /* start ticking     	      */

	while (gameStatus)
	{
		pause();
	}
	signal(SIGALRM, SIG_IGN);
	signal(SIGIO, SIG_IGN);
	// When code reaches here, means that user is loss
	endGame(score, diY, diX);
	attroff(COLOR_PAIR(1));
}

void show()
{
	// tcflush(0, TCIFLUSH);
	maxX = getmaxx(stdscr);
	x = maxX - 20;
	y = getmaxy(stdscr) - 6;
	diY = y;

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
	mvprintw(1, getmaxx(stdscr) - 9, "%d : %d", highScore, score);

	// ----------
	box(stdscr, ACS_VLINE, ACS_HLINE);

	//for clearing screen
	clearDinasourUp(diY, diX);
	isObstacle = rand() % 10; 		   // create obstacle or not
	if (isObstacle == 1)      		   // probability of creating obstacle: 10%
	{					
		cactusNum = rand() % 3;	   // decide the type of cactus
		cactus.x = getmaxx(stdscr) - 20;  // initial x-axis position of cactus
		cactus.y = y;		           // initial y-axis position of cactus
		cactus.type = cactusNum;	   // type of cactus
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
	else
		clearDinasourUp(diY, diX);
	if (diY <= 7)
	{
		isJumping = false;
	}

	obstacle first = queue[(front + 1) % MAX_QUEUE_SIZE]; // closest obstacle from dinosaur
	showObstacle();					//show all cactus in queue

	gameStatus = checkGame(first.y, first.x, diY, diX);
	// Bring back dinosaur

	mvhline(y + 1, 1, '-', getmaxx(stdscr) - 3);
	updateObstacle();
	/* show character you chose*/
	switch (getMode)
	{
	case 'a': case '\n':
		showDinasour(diY, diX);
		break;
	case 'b':
		showPeople(diY, diX);
		break;
	case 'c':
		showAlphaca(diY, diX);
		break;
	case 'd':
		showAmongus(diY, diX);
		break;
	
	}

	refresh();
	usleep(delayTime);
	x -= 7;
	delayTime = computeTime(delayTime);
	userInput = 'q';
}
