/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: otakar
 *
 * Created on 4. června 2017, 1:09
 */

#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "MapLoader.h"

#include <string>

class Game {
public:

    /**
     * Game constructor
     */
    Game() {
        this->drawMenu();
        this->loader = new MapLoader();
    }

    /**
     * Game destructor
     */
    ~Game() {
        delete loader;
        if (level != NULL) {
            delete level;
        }
    }
    void update(int time);

    /**
     * 
     * @return int game status 
     */
    int getGameStatus() const {
        return gameStatus;
    }

    /**
     * 
     * sets game status
     * @param gameStatus
     */
    void setGameStatus(int gameStatus) {
        this->gameStatus = gameStatus;
    }


    Level * initLevel(int levelNumber, const string & levelName, const string & wallName);
    void drawMenu();
    void drawTutorial();
    void spawnAttacker(int in, const string & name);
    void endLevel();
    void saveGame();
    void loadGame();
private:

    void initTowers(int levelNumber);
    MapLoader * loader;
    Level * level = NULL;
    int gameStatus = 1, attackerNumber = 0, towerNumber = 0, money = 1000;
};

#endif /* GAME_H */

