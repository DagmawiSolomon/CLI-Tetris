# CLI Tetris

## Overview

This is a CLI Tetris game implementation created for a C++ class project. The game follows the classic rules of Tetris, where players maneuver falling tetrominoes to create complete horizontal lines, which then disappear. The goal is to prevent the stack of tetrominoes from reaching the top of the playing field for as long as possible.

## Features 
- Classic Tetris gameplay mechanics.
- Random generation of tetrominoes.
- Ability to rotate and move tetrominoes.
- Line clearing functionality.
- Scoring system.
- Game over detection.

## Requirements
- C++ compiler( the program was written using g++ (MinGW.org GCC-6.3.0-1) 6.3.0)

## Installation
- Compile the source code using the provided command:

```cpp
// If you're using mingw 
g++ gameLogic.cpp main.cpp menu.cpp board.cpp -o main
```

## Usage

<h4 style="color:#ff0000;"> Disclaimer: This game was designed for Windows machines. Running it on a different OS could lead to unexpected behavior. </h4>

1. Run the compiled executable (`main` if you used the provided command to compile).
2. Use the arrow keys to navigate and choose from the three menu items.
3. Press `Space` to select the menu item you've chosen.
4. While playing the game, use the arrow keys to move the falling tetrominoes left, right, or down.
5. Press the `Up` arrow key to rotate the tetromino.
6. Try to complete horizontal lines to clear them and earn points.
7. The game ends when the stack of tetrominoes reaches the top of the playing field.
8. Press `R` or `r` to restart the game.

## Credits

### Team members
1. Adonay Ayal
2. Dagmawi Solomon
3. Sofoniyas Shitaye
4. Tomas Solomon
5. Yaphet Gebreyesus
