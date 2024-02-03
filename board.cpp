#include <iostream>
#include <windows.h>

#include "board.h"
#include "menu.h"
#include "gameLogic.h"

using namespace std;

// Function to draw the game canvas on the console screen
void drawCanvas()
{
    // Set the console cursor position to the top-left corner (0, 0)

    // Iterate through each row and column of the game board
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            // Check if the current cell is empty ("")
            if (board[j][i] == "")
                cout << " "; // If empty, print a space to represent an empty cell
            else
                cout << board[j][i]; // If not empty, print the content of the cell
        }

        // Move to the next line after printing a row to create the game board layout
        cout << endl;
    }
}

// Function to add an element to the game board at a specified position
void addElement(int x, int y, string text)
{
    // Get the size of the text parameter
    int textSize = text.size();

    // Iterate through each character in the string
    for (int i = 0; i < textSize; i++)
    {
        // Calculate the adjusted position to add the current character
        // Explanation: (x + i) - (textSize - 1) adjusts for the starting position
        // and ensures the element is placed correctly within the available board width
        int adjustedX = (x + i) - (textSize - 1);

        // Add the current character to the game board at the calculated position
        // Explanation: board[adjustedX][y] = text[i] assigns the character to the specified position
        board[adjustedX][y] = text[i];
    }
}

void drawStats(int x)
{
    addElement(((x - 70) + (x - 70) + 6) / 2, 3, "Stats");

    addElement(x - 70, 5, "Score");
    addElement((x - 70) + 5, 5, to_string(menu::score));

    addElement(x - 70, 7, "Lines");
    addElement((x - 70) + 5, 7, to_string(menu::lines));

    addElement(x - 70, 9, "Level");
    addElement((x - 70) + 5, 9, to_string(menu::level));
}

void drawNext(int x)
{
    addElement(x + 56, 3, "Next");

    drawNextPiece();
}
void drawHelp(int x)
{
    // Help
    addElement(x + 57, 9, "Help");
    addElement(x + 70, 11, "Left Arrow -  move tetromino Left");
    addElement(x + 70, 13, "Right Arrow - move tetromino right");
    addElement(x + 70, 15, "Up Arrow -  rotate tetromino");
    addElement(x + 70, 17, "Down Arrow -  Drop tetromino");
    addElement(x + 70, 19, "R -  Restart");
    addElement(x + 70, 21, "Q - quit game");
}
