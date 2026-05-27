#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    Game game;
    bool running = true;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int lastTick = GetTickCount();
    int tickDelay = 500;

    while (running) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'r' || ch == 'R') {
                game = Game();
            }
            else {
                game.handleInput(ch);
            }
        }
        int now = GetTickCount();
        if (now - lastTick >= tickDelay) {
            game.update();
            lastTick = now;
        }
        system("cls");
        game.draw();

        if (game.isGameOver()) {
            while (true) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 'r' || ch == 'R') {
                        game = Game();
                        break;
                    }
                    else if (ch == 27) {
                        running = false;
                        break;
                    }
                }
                Sleep(100);
            }
        }

        Sleep(30);
    }

    return 0;
}