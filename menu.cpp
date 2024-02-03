#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

#include "menu.h"
#include "board.h"
#include "gameLogic.h"

#include <cmath>

using namespace std;

int navTracker = 0;

int WINDOW_WIDTH;

bool menuVisible = true;
bool gameVisible = false;
bool highScoreVisible = false;
bool helpVisible = false;

void align(int line_length, char pos, string s1, string s2 = "")
{
    int spaces = 0;
    switch (pos)
    {
    case 'c':
        spaces = (line_length - (s1.size() + s2.size())) / 2;
        break;

    case 'r':
        spaces = line_length - (s1.size() + s2.size());
    }
    if (spaces > 0)
        cout << string(spaces, ' ');
    cout << s1 << s2 << endl;
}

string displayMenu(string text, int id)
{

    return (navTracker == id ? ">> " + text + " <<" : text);
}
void Input()
{
    while (_kbhit())
    {
        switch (_getch())
        {
        case 32:
            menuVisible = false;
            if (navTracker == 0)
            {
                gameVisible = true;
            }
            else if (navTracker == 1)
            {
                highScoreVisible = true;
            }
            else if (navTracker == 2)
            {
                helpVisible = true;
            }
            break;
        case 72: // Up arrow key
            if (menuVisible)
            {
                if (navTracker > 0)
                {
                    navTracker--;
                }
                else
                {
                    navTracker = 2;
                }
            }

            break;
        case 80: // Down arrow key
            if (navTracker < 2)
            {
                navTracker++;
            }
            else
            {
                navTracker = 0;
            }
            break;
        case 82:
        case 114:
            if (navTracker == 1 || navTracker == 2)
            {
                gameVisible = false;
                highScoreVisible = false;
                helpVisible = false;
                menuVisible = true;
            }
            else if (navTracker == 0)
            {
                cout << "Game restareted";
            }
            break;
        }
    }
}
void gameMenu()
{
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        WINDOW_WIDTH = (csbi.srWindow.Right - csbi.srWindow.Left + 1);

        cout << string(5, '\n');
        string row1 = R"(########  ####### ########  ######   ######   #####)";
        string row2 = R"(#  ##  #  ##  ##  #  ##  #  ##  ##     ##    ##   ##)";
        string row3 = R"(   ##     ##         ##     ##  ##     ##    ##     )";
        string row4 = R"(   ##     ####       ##     #####      ##     #####)";
        string row5 = R"(   ##     ##         ##     ####       ##         ##)";
        string row6 = R"(   ##     ##  ##     ##     ## ##      ##    ##   ##)";
        string row7 = R"(   ##     #######    ##     ###  ##   ######   #####)";

        // Print each row separately
        align(WINDOW_WIDTH, 'c', row1);
        align(WINDOW_WIDTH, 'c', row2);
        align(WINDOW_WIDTH, 'c', row3);
        align(WINDOW_WIDTH, 'c', row4);
        align(WINDOW_WIDTH, 'c', row5);
        align(WINDOW_WIDTH, 'c', row6);
        align(WINDOW_WIDTH, 'c', row7);

        cout << string(2, '\n');
        align(WINDOW_WIDTH, 'c', displayMenu("Play game", 0));
        align(WINDOW_WIDTH, 'c', displayMenu("Highscore", 1));
        align(WINDOW_WIDTH, 'c', displayMenu("Help", 2));

        cout << string(5, '\n');
    }
}

void Highscore()
{
    cout << string(5, '\n');

    align(WINDOW_WIDTH, 'c', "Highscore");
    cout << endl;
    align(WINDOW_WIDTH, 'c', to_string(highscore));
    cout << endl;
    align(WINDOW_WIDTH, 'c', "Press R to return");
}

void help()
{
    cout << string(5, '\n');
    align(WINDOW_WIDTH, 'c', "Help");
    cout << endl;
    align(WINDOW_WIDTH, 'c', "1. Controls");
    align(WINDOW_WIDTH, 'c', "    Use the following keys to control the game");
    align(WINDOW_WIDTH, 'c', "        Left Arrow : Move tetromino left");
    align(WINDOW_WIDTH, 'c', "        Right Arrow : Move tetromino right");
    align(WINDOW_WIDTH, 'c', "        Down Arrow : Drop");
    align(WINDOW_WIDTH, 'c', "        Up Arrow : Rotate tetromino");
    align(WINDOW_WIDTH, 'c', "        Q : Quit the game");

    cout << endl;
    // Scoring Section
    align(WINDOW_WIDTH, 'c', "2. Scoring");
    align(WINDOW_WIDTH, 'c', "    Clearing Lines : Completing lines will earn you points.");
    align(WINDOW_WIDTH, 'c', "    Leveling Up : As you accumulate points,");
    align(WINDOW_WIDTH, 'c', "    you will advance to higher levels,");
    align(WINDOW_WIDTH, 'c', "    increasing the game's difficulty.");

    cout << endl;
    // Game Over Section
    align(WINDOW_WIDTH, 'c', "3. Game Over");
    align(WINDOW_WIDTH, 'c', "    The game ends when the stack of tetrominos reaches the top of the grid.");

    cout << endl;
    align(WINDOW_WIDTH, 'c', "Have fun and aim for the highest score!");
}

void drawBorders(int width, int height, string row_char, string col_char)
{
    int x, y;
    for (x = 0; x < width; x++)
    {
        cout << row_char;
    }
    cout << endl;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1)
            {
                cout << col_char;
            }
            else if (x == (width / 2) - 2 && y == ((height - 1) / 2))
            {
                cout << "Score";
                x += 4;
            }
            else if (x == (width / 2) && y == ((height - 1) / 2) + 1)
            {
                cout << "0";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    for (x = 0; x < width; x++)
    {
        cout << row_char;
    }
    cout << endl;
}
void playGame()
{

    int x = CANVAS_WIDTH / 2;
    drawStats(x);
    drawNext(x);
    drawTetrisBoard();
    drawHelp(x);
    drawCanvas();
    Logic();
}