// In this code, we have just skins and functions to clear those skins
#include <ncurses.h>
void people1(int y, int x)
{
	mvprintw(y - 11, x, "     $$$");
	mvprintw(y - 10, x, "    $$$$$");
	mvprintw(y - 9, x, "    $$$$$");
	mvprintw(y - 8, x, "     $$$");
	mvprintw(y - 7, x, "   $$$$$$$$  ");
	mvprintw(y - 6, x, "  $ $$$$$$ $");
	mvprintw(y - 5, x, " $  $$$$$$ $");
	mvprintw(y - 4, x, "    $$$$$$ ");
	mvprintw(y - 3, x, "$$$ $$$ $$$ ");
	mvprintw(y - 2, x, "  $$$$   $$");
	mvprintw(y - 1, x, "          $$");
	mvprintw(y, x, "          $$$");
}
void people2(int y, int x)
{
	mvprintw(y - 11, x, "     $$$");
	mvprintw(y - 10, x, "    $$$$$");
	mvprintw(y - 9, x, "    $$$$$");
	mvprintw(y - 8, x, "     $$$");
	mvprintw(y - 7, x, "  $$$$$$$$$ $");
	mvprintw(y - 6, x, " $  $$$$$$ $");
	mvprintw(y - 5, x, "  $ $$$$$$  ");
	mvprintw(y - 4, x, "    $$$$$$  ");
	mvprintw(y - 3, x, "    $$$$$$ ");
	mvprintw(y - 2, x, " $$  $$$$  ");
	mvprintw(y - 1, x, "  $$$$  $$$ ");
	mvprintw(y, x, "         $$$ ");
}
void amongus1(int y, int x)
{
	mvprintw(y - 12, x, "      (-)  (-)  ");
	mvprintw(y - 11, x, "       \\  \\/    ");
	mvprintw(y - 10, x, "         ||     ");
	mvprintw(y - 9, x, "         ||     ");
	mvprintw(y - 8, x, "    ,_________  ");
	mvprintw(y - 7, x, "  /   ,--------|");
	mvprintw(y - 6, x, "/-|   |        |");
	mvprintw(y - 5, x, "| |   |        |");
	mvprintw(y - 4, x, "| |   '--------|");
	mvprintw(y - 3, x, "| |            |");
	mvprintw(y - 2, x, "\\_|            |");
	mvprintw(y - 1, x, "  |    ___     |");
	mvprintw(y, x, "  \\_,_|    \\_._|");
}

void amongus2(int y, int x)
{
	mvprintw(y - 12, x, "      (-)  (-)  ");
	mvprintw(y - 11, x, "       \\  \\/    ");
	mvprintw(y - 10, x, "         ||     ");
	mvprintw(y - 9, x, "         ||     ");
	mvprintw(y - 8, x, "    ,_________  ");
	mvprintw(y - 7, x, "  /   ,--------|");
	mvprintw(y - 6, x, "/-|   |        |");
	mvprintw(y - 5, x, "| |   |        |");
	mvprintw(y - 4, x, "| |   '--------|");
	mvprintw(y - 3, x, "| |            |");
	mvprintw(y - 2, x, "\\_|            |");
	mvprintw(y - 1, x, "  |    ___     |");
	mvprintw(y, x, "  |_,_/`  |_,_/");
}

void alphaca1(int y, int x)
{
	mvprintw(y - 11, x, "          A~~~A");
	mvprintw(y - 10, x, "         ( .I. )");
	mvprintw(y - 9, x, "         (  ~ )");
	mvprintw(y - 8, x, "         (  P )");
	mvprintw(y - 7, x, "         (  A )");
	mvprintw(y - 6, x, "()       (  C )   ");
	mvprintw(y - 5, x, "//('~~~~O'  A )");
	mvprintw(y - 4, x, "(              )");
	mvprintw(y - 3, x, "(  )      (   )  ");
	mvprintw(y - 2, x, "(  ) )~~( (   ) ");
	mvprintw(y - 1, x, "(_/( )~~(_(  ) ");
	mvprintw(y, x, "  (_/    (_/");
}

void alphaca2(int y, int x)
{
	mvprintw(y - 11, x, "          A~~~A");
	mvprintw(y - 10, x, "         ( .I. )");
	mvprintw(y - 9, x, "         (  ~ )");
	mvprintw(y - 8, x, "         (  P )");
	mvprintw(y - 7, x, "         (  A )");
	mvprintw(y - 6, x, "()       (  C )   ");
	mvprintw(y - 5, x, "//('~~~~O'  A )");
	mvprintw(y - 4, x, "(              )");
	mvprintw(y - 3, x, "(  )      (   )  ");
	mvprintw(y - 2, x, "(  ) )~~( (  )");
	mvprintw(y - 1, x, "(  )_/~~( (_/  ");
	mvprintw(y, x, "(_/     (_/");
}

void dinasour1(int y, int x)
{
	mvprintw(y - 11, x, "         $$$$$$$");
	mvprintw(y - 10, x, "       $$  $$$$$");
	mvprintw(y - 9, x, "       $$$$$$$$$");
	mvprintw(y - 8, x, "$      $$$      ");
	mvprintw(y - 7, x, "$$     $$$$$$$  ");
	mvprintw(y - 6, x, "$$$   $$$$$     ");
	mvprintw(y - 5, x, " $$  $$$$$$$$$$ ");
	mvprintw(y - 4, x, "  $$$$$$$$$$    ");
	mvprintw(y - 3, x, "    $$$$$$$$    ");
	mvprintw(y - 2, x, "     $$$$$$     ");
	mvprintw(y - 1, x, "     $    $$$   ");
	mvprintw(y, x, "     $$         ");
}

void dinasour2(int y, int x)
{
	mvprintw(y - 11, x, "         $$$$$$$");
	mvprintw(y - 10, x, "       $$  $$$$$");
	mvprintw(y - 9, x, "       $$$$$$$$$");
	mvprintw(y - 8, x, "$      $$$      ");
	mvprintw(y - 7, x, "$$     $$$$$$$  ");
	mvprintw(y - 6, x, "$$$   $$$$$     ");
	mvprintw(y - 5, x, " $$  $$$$$$$$$$ ");
	mvprintw(y - 4, x, "  $$$$$$$$$$    ");
	mvprintw(y - 3, x, "    $$$$$$$$    ");
	mvprintw(y - 2, x, "     $$$$$$     ");
	mvprintw(y - 1, x, "     $$$  $     ");
	mvprintw(y, x, "          $$    ");
}
void cactus1(int y, int x)
{
	mvprintw(y - 5, x, "  ## #");
	mvprintw(y - 4, x, "  ## #");
	mvprintw(y - 3, x, "# ####");
	mvprintw(y - 2, x, "####  ");
	mvprintw(y - 1, x, "  ## #");
	mvprintw(y, x, "  ###");
}

void cactus2(int y, int x)
{
	mvprintw(y - 5, x, "  ##");
	mvprintw(y - 4, x, "# ##");
	mvprintw(y - 3, x, "# ## #");
	mvprintw(y - 2, x, " ####");
	mvprintw(y - 1, x, "  ##");
	mvprintw(y, x, "  ##");
}
void cactus3(int y, int x)
{
	mvprintw(y - 4, x, "  #");
	mvprintw(y - 3, x, "# # #");
	mvprintw(y - 2, x, "####");
	mvprintw(y - 1, x, " ##");
	mvprintw(y, x, " ##");
}

void sun(int y, int x)
{
	mvprintw(y - 8, x, "         $           $                $     ");
	mvprintw(y - 7, x, "              $       $        $            ");
	mvprintw(y - 6, x, "        $         $$$$$$$$ $        $       ");
	mvprintw(y - 5, x, "                $$        $$                ");
	mvprintw(y - 4, x, "  $    $       $$          $$    $       $  ");
	mvprintw(y - 3, x, "                $$        $$                ");
	mvprintw(y - 2, x, "          $       $$$$$$$$   $              ");
	mvprintw(y - 1, x, "              $      $            $         ");
	mvprintw(y, x, "    $                 $                $    ");
}

void moon(int y, int x)
{
	mvprintw(y - 6, x, "@                  $$ $$$$$      @          ");
	mvprintw(y - 5, x, "           @    $$$                         ");
	mvprintw(y - 4, x, "              $$$$                          ");
	mvprintw(y - 3, x, "    @         $$$$                      @   ");
	mvprintw(y - 2, x, "               $$$                 @        ");
	mvprintw(y - 1, x, "                $$$$                        ");
	mvprintw(y, x, "         @         \"$$$$$$$                @");
}

void showLoss(int y, int x)
{
	mvprintw(y - 6, x - 25, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	mvprintw(y - 5, x - 25, "xxxxxxxxxxxX    xx          xx  xxxxxxxxxxxxxx");
	mvprintw(y - 4, x - 25, "xx            xxx xx        xx  xxxxxxxxxxxxxx");
	mvprintw(y - 3, x - 25, "xx           xxx  xxxx      xx  xxxxxxxxxxxxxx");
	mvprintw(y - 2, x - 25, "xxxxxxxxxxxxxxxxxxxxxxxx    xx  xxxxxxxxxxxxxx");
	mvprintw(y - 1, x - 25, "xxxxx      xxxx     xxxxx   xx  xxxxxxxxxxxxxx");
	mvprintw(y, x - 25, "xx        xxx          xxx  xx  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	mvprintw(y + 1, x - 25, "xx        xx            xx  xx  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	mvprintw(y + 2, x - 25, "xx       xx             xx  xx  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	mvprintw(y + 3, x - 25, "Press 'r' to play again!");
	mvprintw(y + 4, x - 25, "Or 'q' to exit from game.");
}

void showTeam1(int x, int y)
{
	mvprintw(x - 7, y - 25, "  1                                                11111111111111111");
	mvprintw(x - 6, y - 25, "  11                                            11  1111111111111111");
	mvprintw(x - 5, y - 25, "1111111   11111       111          1111  111        1111111111111111");
	mvprintw(x - 4, y - 25, "  11     1    11   11    11       1   11 11 1       1111111111111111");
	mvprintw(x - 3, y - 25, "  11     11111    11   11111    111   11    11      1111111111111111");
	mvprintw(x - 2, y - 25, "  11     11       11  111  11   11    1     11      1111111111111111");
	mvprintw(x - 1, y - 25, "  \"1111   1111111  111     11 11`    111     111    1111111111111111");
}

void clearCactus1(int y, int x)
{
	mvprintw(y - 5, x, "       ");
	mvprintw(y - 4, x + 7, "             ");
	mvprintw(y - 3, x + 7, "             ");
	mvprintw(y - 2, x + 7, "             ");
	mvprintw(y - 1, x + 7, "             ");
	mvprintw(y, x + 7, "             ");

	// if (x <= 10) {
	// 	mvprintw(y-4, 0, "     ");
	// 	mvprintw(y-3, 0, "     ");
	// 	mvprintw(y-2, 0, "     ");
	// 	mvprintw(y-1, 0, "     ");
	// 	mvprintw(y, 0,   "     ");
	// }
}

void clearDinasourDown(int diY, int diX)
{
	mvprintw(diY + 1, diX, "                ");
	mvprintw(diY + 2, diX, "                ");
	mvprintw(diY + 3, diX, "                ");
	mvprintw(diY + 4, diX, "                ");
	mvprintw(diY + 5, diX, "                ");
	mvprintw(diY + 6, diX, "                ");
	mvprintw(diY + 7, diX, "                ");
}

void clearDinasourUp(int diY, int diX)
{
	mvprintw(diY - 12, diX, "                ");
	mvprintw(diY - 13, diX, "                ");
	mvprintw(diY - 14, diX, "                ");
	mvprintw(diY - 15, diX, "                ");
	mvprintw(diY - 16, diX, "                ");
	mvprintw(diY - 17, diX, "                ");
	mvprintw(diY - 18, diX, "                ");
	mvprintw(diY - 19, diX, "                ");
}
