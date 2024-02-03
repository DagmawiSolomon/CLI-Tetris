#include <vector>
using namespace std;
#ifndef gameLogic
#define gameLogic

class Tetromino
{
public:
    int x = 10;
    int y = 0;
    int dimension = 3;
    int rotation = 0;
    vector<int> shape;
};

Tetromino spawn();
void drawNextPiece();
void Logic();
void drawTetrisBoard();
void gameInput();
#endif