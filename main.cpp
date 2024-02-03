#include <windows.h>

#include "menu.h"
#include "board.h"
#include "gameLogic.h"

std::string board[CANVAS_WIDTH][CANVAS_HEIGHT];

bool gameOver = false;
int score = 0;
int level = 0;
int lines = 0;
int highscore = 0;
int main()
{
    while (!gameOver)
    {
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (menuVisible)
        {
            system("cls");
            gameMenu();
            Input();
        }
        else if (gameVisible)
        {
            playGame();
            gameInput();
        }
        else if (highScoreVisible)
        {
            system("cls");
            Highscore();
            Input();
        }
        else if (helpVisible)
        {
            system("cls");
            help();
            Input();
        }
        Sleep(150);
    }
}