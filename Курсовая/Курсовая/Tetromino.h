#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>

class Tetromino {
private:
    std::vector<std::vector<int>> shape;
    int color;

public:
    Tetromino(int type);

    std::vector<std::vector<int>> getShape() const;
    int getColor() const;

    void rotate();
};

#endif