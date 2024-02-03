#include <iostream>
#include "gameLogic.h"
using namespace std;

#ifndef menu
#define menu

extern bool helpVisible;
extern bool highScoreVisible;
extern bool gameVisible;
extern bool menuVisible;
extern bool gameOver;

extern int score;
extern int lines;
extern int level;
extern int highscore;

void align(int line_length, char pos, string s1, string s2);

string displayMenu(string text, int id);
void gameMenu();

void Input();
void Highscore();

void help();

void drawBorders(int width, int height, string row_char, string col_char);
void playGame();

#endif