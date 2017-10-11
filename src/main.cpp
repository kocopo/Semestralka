

#include <cstdlib>
#include <ncurses.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>

#include "Game.h"
using namespace std;
using namespace std::chrono;

int kbhit(void);
void handleInput(Game * game, int ch);

int main(int argc, char** argv) {
    initscr();
    noecho();
    curs_set(0);
    int ch;
    milliseconds ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());
    Game * game = new Game();
    while (game->getGameStatus() != 0) {
        game->update(ms.count());
        if ((ch = kbhit()) != 0) {
            if (ch == 'q' || ch == 'Q')game->setGameStatus(0);
            handleInput(game, ch);
        }
    }
    delete game;

    endwin();
    return 0;
}

/**
 * Methods waits for input from user while other things run in background
 * Method was taken over from https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
 * @return Int value of a character 
 */
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getch();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        return ch;
    }

    return 0;
}

/**
 * Handles input
 * @param game which to send input
 * @param ch input
 */
void handleInput(Game * game, int ch) {
    if (game->getGameStatus() == 1) {
        switch (ch) {
            case 't':
            case 'T':
                game->drawTutorial();
                game->setGameStatus(2);
                break;
            case 'a':
            case 'A':
                game->setGameStatus(3);
                game->initLevel(1, "src/res/map.txt", "src/res/walls.txt");
                break;
            case 's':
            case 'S':
                game->setGameStatus(3);
                game->initLevel(2, "src/res/map.txt", "src/res/walls.txt");
                break;
            case 'D':
            case 'd':
                game->setGameStatus(3);
                game->initLevel(3, "src/res/map.txt", "src/res/walls.txt");
                break;
            case 'l':
            case 'L':
                game->setGameStatus(3);
                game->loadGame();
                break;
            default:
                break;
        }
    } else if (game->getGameStatus() == 2) {
        switch (ch) {
            case 'b':
            case 'B':
                game->drawMenu();
                game->setGameStatus(1);
                break;
            default:
                break;
        }
    } else if (game->getGameStatus() == 3) {
        switch (ch) {
            case 'w':
            case 'W':
                game->saveGame();
                break;
            case 'a':
            case 'A':
                game->spawnAttacker(1, "orc");
                break;
            case 's':
            case 'S':
                game->spawnAttacker(1, "goblin");
                break;
            case 'd':
            case 'D':
                game->spawnAttacker(1, "wolf");
                break;
            case 'y':
            case 'Y':
                game->spawnAttacker(2, "orc");
                break;
            case 'x':
            case 'X':
                game->spawnAttacker(2, "goblin");
                break;
            case 'c':
            case 'C':
                game->spawnAttacker(2, "wolf");
                break;
            case 'p':
            case 'P':
                while (true) {
                    if (kbhit() != 0)break;
                }
                break;
            case 'b':
            case 'B':
                game->endLevel();
                game->setGameStatus(1);
                game->drawMenu();
                break;
            default:
                break;
        }
    }
}
