#ifndef GAME_H
#define GAME_H

#include "Tetromino.h"

class Game {
private:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    int field[HEIGHT][WIDTH];
    int colorField[HEIGHT][WIDTH];

    Tetromino* currentPiece;
    int currentX, currentY;
    bool gameOver;
    int score;

    void spawnNewPiece();
    bool isValidMove(int newX, int newY, const std::vector<std::vector<int>>& shape) const;
    void mergePiece();
    void clearLines();
public:
    Game();
    ~Game();

    void handleInput(char key);
    void update();
    void draw() const;

    bool isGameOver() const;
    int getScore() const;
};

#endif