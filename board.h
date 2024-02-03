
#ifndef gameBoard
#define gameBoard

#include <iostream>
#include <windows.h>

// Initialize the WIDTH of the game canvas
constexpr const int CANVAS_HEIGHT = 30;
constexpr const int CANVAS_WIDTH = 167;

// Initialize the dimension of the tetris board
constexpr const int BOARD_WIDTH = 22;
constexpr const int BOARD_HEIGHT = 21;

// Initialize a string array to represent the game board
extern std::string board[CANVAS_WIDTH][CANVAS_HEIGHT];

// Function to draw the game canvas on the console screen
void drawCanvas();

void drawNext(int x);

// Function to add an element to the game board at a specified position
void addElement(int x, int y, std::string text);

// Function to draw the stats section
void drawStats(int x);

// Function to draw the help section
void drawHelp(int x);

#endif // TETRIS_FUNCTIONS_H
