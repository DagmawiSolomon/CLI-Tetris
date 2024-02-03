#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <numeric>
#include <windows.h>
#include "board.h"
#include "gameLogic.h"
#include "menu.h"
#include <fstream>

using namespace std;

const int X = (CANVAS_WIDTH / 2);
int adjX = X - (BOARD_WIDTH / 2);
int adjY = 5;

bool isSpawining = true;

// Function to spawn a random Tetromino
Tetromino
spawn()
{
    // An array to represent the 7 different Tetromino pieces
    char tetrominos[7] = {'I', 'O', 'L', 'J', 'S', 'Z', 'T'};

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random index to select a Tetromino from the array
    int randomIndex = std::rand() % 7;

    // Get a random character from the tetrominos array
    char randomTetromino = tetrominos[randomIndex];
    Tetromino currentTetromino;

    // Set the properties of the currentTetromino based on the selected random Tetromino
    switch (randomTetromino)
    {
    case 'I':
        currentTetromino.dimension = 4;
        currentTetromino.shape = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        break;

    case 'O':
        currentTetromino.dimension = 2;
        currentTetromino.shape = {1, 1, 1, 1};
        break;

    case 'L':
        currentTetromino.shape = {0, 0, 1, 1, 1, 1, 0, 0, 0};
        break;

    case 'J':
        currentTetromino.shape = {1, 0, 0, 1, 1, 1, 0, 0, 0};
        break;

    case 'S':
        currentTetromino.shape = {0, 1, 1, 1, 1, 0, 0, 0, 0};
        break;

    case 'Z':
        currentTetromino.shape = {1, 1, 0, 0, 1, 1, 0, 0, 0};
        break;

    case 'T':
        currentTetromino.shape = {1, 1, 1, 0, 1, 0, 0, 0, 0};
        break;

    default:
        break;
    }
    // Return the initialized currentTetromino
    return currentTetromino;
}

// create instances of the tetromino class
Tetromino tetromino = spawn();
Tetromino NextPiece = spawn();

// Function to draw the next piece
void drawNextPiece()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j < NextPiece.dimension)
            {
                int index = i * NextPiece.dimension + j;
                if (NextPiece.shape[index] == 1)
                    addElement(X + j + 54, i + 5, "m");
                else
                    addElement(X + j + 54, i + 5, " ");
            }
            else
            {
                addElement(X + j + 54, i + 5, " ");
            }
        }
    }
}

// Function to rotate tetrominos
int rotateTetrmino(int x, int y)
{
    switch (tetromino.rotation)
    {
    case 0:
        return (y - tetromino.y) * tetromino.dimension + (x - tetromino.x);
        break;

    case 1:
        return (x - tetromino.x) * tetromino.dimension + (tetromino.y + (tetromino.dimension - 1) - y);
        break;

    default:
        break;
    }
}

// Function to check if rows are completed
void CheckAndRemoveFullRows()
{
    if (isSpawining)
    {

        for (int i = BOARD_HEIGHT - 1; i > 0; i--)
        {
            bool rowFull = true;

            for (int j = 1; j < BOARD_WIDTH - 1; j++)
            {
                if (board[adjX + j][adjY + i] == ".")
                {
                    rowFull = false;
                    break;
                }
            }

            for (int j = 1; j < BOARD_WIDTH - 1; j++)
            {
                if (board[adjX + j][adjY + i] == "#")
                {
                    if (menu::lines <= 20 - i)
                    {
                        menu::lines++;
                    }
                }
            }

            if (rowFull)
            {
                if (menu::lines > 0)
                {
                    menu::lines--;
                }

                for (int k = i; k > 0; k--)
                {
                    for (int j = 1; j < BOARD_WIDTH - 1; j++)
                    {
                        board[adjX + j][adjY + k] = board[adjX + j][adjY + k - 1];
                    }
                }
                i++;
                menu::score += 5;
                if (menu::score > menu::highscore)
                {
                    menu::highscore = menu::score;
                }
                if (menu::score % 25 == 0)
                {
                    menu::level++;
                }
            }
        }
    }
    else
    {
        menu::lines = 0;
    }
}

// Function to make the tetrominos permanent part of the board
void MergeTetromino()
{
    for (int i = 0; i < tetromino.dimension; i++)
    {
        for (int j = 0; j < tetromino.dimension; j++)
        {
            int boardX = adjX + tetromino.x + j;
            int boardY = adjY + tetromino.y + i;

            int index;

            switch (tetromino.rotation)
            {
            case 0:
                index = i * tetromino.dimension + j;
                break;

            case 1:
                if (tetromino.dimension == 4)
                    index = j * tetromino.dimension + i;
                else
                    index = j * tetromino.dimension + (tetromino.dimension - 1 - i);

                break;

            default:
                break;
            }

            if (tetromino.shape[index] == 1)
            {

                if (boardX >= 73 && boardX < 93 && boardY >= 5 && boardY < BOARD_HEIGHT + 5)
                {

                    board[boardX][boardY] = "#";
                }
            }
        }
    }
    CheckAndRemoveFullRows();
}

// Function to check if the tetrominos move if allowed
bool isValidMove(int xOffset, int yOffset)
{
    for (int i = 0; i < tetromino.dimension; i++)
    {
        for (int j = 0; j < tetromino.dimension; j++)
        {
            int boardX = adjX + tetromino.x + j + xOffset;
            int boardY = adjY + tetromino.y + i + yOffset;

            int index;

            switch (tetromino.rotation)
            {
            case 0:
                index = (i)*tetromino.dimension + (j);
                break;

            case 1:
                if (tetromino.dimension == 4)
                    index = (j)*tetromino.dimension + (i);
                else
                    index = (j)*tetromino.dimension + (tetromino.dimension - 1 - (i));
                break;

            default:
                break;
            }
            if (tetromino.shape[index] == 1)
            {

                if (boardX < adjX + 1 || boardX >= adjX + BOARD_WIDTH - 1 || boardY < adjY || boardY >= adjY + BOARD_HEIGHT || board[boardX][boardY] == "#")
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to Clear board when the player clicks restart
void clearboard()
{

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {

            if (j == 0 || j == BOARD_WIDTH - 1)
            {
                addElement(adjX + j, adjY + i, "#");
            }
            else
            {
                addElement(adjX + j, adjY + i, ".");
            }
        }
    }
}

// Function to listen to user input
void gameInput()
{
    while (_kbhit())
    {
        switch (_getch())
        {

        case 72: // Up arrow key
            if (tetromino.rotation < 1)
            {
                tetromino.rotation++;
            }
            else
            {
                tetromino.rotation = 0;
            }
            break;
        case 80:

            if (tetromino.rotation == 0)
                tetromino.y += (BOARD_HEIGHT - 1) - (tetromino.y + (tetromino.dimension == 2 ? tetromino.dimension - 1 : (tetromino.dimension == 2 ? tetromino.dimension - 3 : tetromino.dimension - 2))) - menu::lines;
            else if (tetromino.rotation == 1)
                tetromino.y += (BOARD_HEIGHT - 1) - (tetromino.y + tetromino.dimension) - menu::lines;

            break;
        case 75:
            if (isValidMove(-1, 0))
            {
                tetromino.x--;
            }
            break;
        case 77:
            if (isValidMove(1, 0))
            {
                tetromino.x++;
            }
            break;
        case 81:
        case 113:
            highScoreVisible = false;
            gameVisible = false;
            helpVisible = false;
            menuVisible = true;
            clearboard();
            menu::lines = 0;
            menu::level = 0;
            menu::score = 0;
            tetromino.y = 0;

            break;
        case 114:
        case 82:
            menu::lines = 0;
            menu::level = 0;
            menu::score = 0;
            clearboard();
            tetromino.y = 0;
            isSpawining = true;
            break;

        default:
            break;
        }
    }
}

// Function to draw the tetris board
void drawTetrisBoard()
{
    addElement(X + 2, 3, "TETRIS");

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {

            if (j == 0 || j == BOARD_WIDTH - 1)
            {
                addElement(adjX + j, adjY + i, "#");
            }
            if (isSpawining)
            {
                if (j >= tetromino.x && j < tetromino.x + tetromino.dimension &&
                    i >= tetromino.y && i < tetromino.y + tetromino.dimension)
                {
                    int index = rotateTetrmino(j, i);
                    addElement(adjX + j, adjY + i, (tetromino.shape[index] == 1) ? "m" : (board[adjX + j][adjY + i] == "#") ? "#"
                                                                                                                            : ".");
                }
                else if (board[adjX + j][adjY + i] == "#")
                {
                    addElement(adjX + j, adjY + i, "#");
                }

                else if (board[adjX + j][adjY + i] != "#")

                {
                    addElement(adjX + j, adjY + i, ".");
                }
            }
            else
            {
                addElement(adjX + j, adjY + i, board[adjX + j][adjY + i]);
            }
        }
    }

    for (int m = 0; m < BOARD_WIDTH; m++)
    {
        addElement(adjX + m, BOARD_HEIGHT + 5, "#");
    }
}

// Function to display game over message
void displayMessage(string text, int x, int y)
{
    int length = text.size();
    for (int i = 0; i < length; i++)
    {
        board[x + i][y] = text[i];
    }
}

// Main game logic function
void Logic()
{

    if (isValidMove(0, 1))
    {
        tetromino.y++;
    }
    else
    {
        MergeTetromino();
        if (menu::lines < 20)
        {
            tetromino = NextPiece;
            NextPiece = spawn();
        }
        else
        {
            isSpawining = false;
            displayMessage("GAME OVER!", 78, 15);
            displayMessage("press r to restart", 74, 16);
        }
    }
}
