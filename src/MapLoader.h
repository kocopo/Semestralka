/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapLoader.h
 * Author: otakar
 *
 * Created on 11. května 2017, 18:31
 */

#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Level.h"
#include "Attacker.h"
#include "Tower.h"

class MapLoader {
public:

    MapLoader() {
    }
    Level * loadMap(int levelNumber, const string & levelName, const string & wallsName);

    void saveGame(Level * level);
    Level * loadGame();
    void loadAttacker(Level * level, const string & attackerName, int x, int y, int ID);
    void loadTower(Level * level, const string & towerName, int ID);
    vector<int> loadNumberOfTurrets(int levelNumber);
private:
    void loadWalls(Level * level, int levelNumber, const string & wallsName);
};

#endif /* MAPLOADER_H */

