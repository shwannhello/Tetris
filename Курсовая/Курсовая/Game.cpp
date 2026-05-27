#include "Game.h"
#include <iostream>
#include <windows.h>

using namespace std;

Game::Game() : currentPiece(nullptr), currentX(WIDTH / 2 - 2), currentY(0), gameOver(false), score(0) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            field[i][j] = 0;
            colorField[i][j] = 0;
        }
    }
    spawnNewPiece();
}

Game::~Game() {
    delete currentPiece;
}

void Game::spawnNewPiece() {
    delete currentPiece;
    currentPiece = new Tetromino(rand() % 7);
    currentX = WIDTH / 2 - 2;
    currentY = 0;

    if (!isValidMove(currentX, currentY, currentPiece->getShape())) {
        gameOver = true;
    }
}

bool Game::isValidMove(int newX, int newY, const std::vector<std::vector<int>>& shape) const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                int x = newX + j;
                int y = newY + i;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || y < 0) {
                    return false;
                }
                if (y >= 0 && field[y][x] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Game::mergePiece() {
    auto shape = currentPiece->getShape();
    int color = currentPiece->getColor();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] != 0) {
                int x = currentX + j;
                int y = currentY + i;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    field[y][x] = 1;
                    colorField[y][x] = color;
                }
            }
        }
    }
    clearLines();
    spawnNewPiece();
}

void Game::clearLines() {
    int linesCleared = 0;
    for (int y = HEIGHT - 1; y >= 0; ) {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x) {
            if (field[y][x] == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            for (int row = y; row > 0; --row) {
                for (int x = 0; x < WIDTH; ++x) {
                    field[row][x] = field[row - 1][x];
                    colorField[row][x] = colorField[row - 1][x];
                }
            }
            for (int x = 0; x < WIDTH; ++x) {
                field[0][x] = 0;
                colorField[0][x] = 0;
            }
            linesCleared++;
        }
        else {
            y--;
        }
    }

    if (linesCleared > 0) {
        score += linesCleared * 100;
    }
}

void Game::handleInput(char key) {
    if (gameOver) return;

    switch (key) {
    case 'a':
        if (isValidMove(currentX - 1, currentY, currentPiece->getShape())) {
            currentX--;
        }
        break;
    case 'd':
        if (isValidMove(currentX + 1, currentY, currentPiece->getShape())) {
            currentX++;
        }
        break;
    case 's':
        if (isValidMove(currentX, currentY + 1, currentPiece->getShape())) {
            currentY++;
        }
        else {
            mergePiece();
        }
        break;
    case 'w':
    {
        Tetromino temp = *currentPiece;
        temp.rotate();
        if (isValidMove(currentX, currentY, temp.getShape())) {
            currentPiece->rotate();
        }
    }
    break;
    }
}

void Game::update() {
    if (gameOver) return;

    if (isValidMove(currentX, currentY + 1, currentPiece->getShape())) {
        currentY++;
    }
    else {
        mergePiece();
    }
}

void Game::draw() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int cellColor = colorField[y][x];
            if (field[y][x] != 0) {
                SetConsoleTextAttribute(hConsole, cellColor);
                cout << "[]";
            }
            else {
                bool isCurrent = false;
                if (currentPiece) {
                    auto shape = currentPiece->getShape();
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if (shape[i][j] && y == currentY + i && x == currentX + j) {
                                SetConsoleTextAttribute(hConsole, currentPiece->getColor());
                                cout << "[]";
                                isCurrent = true;
                                break;
                            }
                        }
                        if (isCurrent) break;
                    }
                }
                if (!isCurrent) {
                    SetConsoleTextAttribute(hConsole, 8);
                    cout << "..";
                }
            }
        }
        cout << endl;
    }

    SetConsoleTextAttribute(hConsole, 15);
    cout << "Score: " << score << endl;
    if (gameOver) {
        cout << "GAME OVER! Press R to restart" << endl;
    }
    else {
        cout << "Controls: A(<-) D(->) S(down) W(rotate)" << endl;
    }
}

bool Game::isGameOver() const {
    return gameOver;
}

int Game::getScore() const {
    return score;
}