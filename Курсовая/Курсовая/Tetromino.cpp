#include "Tetromino.h"
#include <algorithm>
const std::vector<std::vector<std::vector<int>>> shapes = {
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    }
};

const std::vector<int> colors = { 11, 14, 13, 12, 9, 10, 5 };

Tetromino::Tetromino(int type) {
    if (type >= 0 && type < (int)shapes.size()) {
        shape = shapes[type];
        color = colors[type];
    }
    else {
        shape = shapes[0];
        color = colors[0];
    }
}

std::vector<std::vector<int>> Tetromino::getShape() const {
    return shape;
}

int Tetromino::getColor() const {
    return color;
}

void Tetromino::rotate() {
    int n = shape.size();
    std::vector<std::vector<int>> rotated(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
}