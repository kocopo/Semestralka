/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <string>

#include "Game.h"
#include "Level.h"
#include "Attacker.h"
#include "MapLoader.h"

/**
 * Draws menu to screen
 * */
void Game::drawMenu() {
    clear();
    mvprintw(0, 0, "t - tutorial");
    mvprintw(1, 0, "a - level 1");
    mvprintw(2, 0, "s - level 2");
    mvprintw(3, 0, "d - level 3");
    mvprintw(4, 0, "l - load game");
    mvprintw(5, 0, "q - quit");
   
    refresh();
}

/**
 * draws tutorial to screen
 */
void Game::drawTutorial() {
    clear();
    mvprintw(0, 0, "Controls are described at map");
    mvprintw(1, 0, "You win if 3 of your attackers pass through the map");
    mvprintw(2, 0, "there are 3 effects:");
    mvprintw(3, 0, "freeze - movement speed halved");
    mvprintw(4, 0, "shredArmor - armor halved");
    mvprintw(5, 0, "weaken - damage halved");
    mvprintw(6, 0, "3 attackers:");
    mvprintw(7, 0, "orc - strong , slow attack speed");
    mvprintw(8, 0, "goblin - normal health, damage, etc...");
    mvprintw(9, 0, "wolf - weak, quick attack");
    mvprintw(10, 0, "3 towers:");
    mvprintw(11, 0, "bombard - strong damage and health, slow attack, far reach");
    mvprintw(12, 0, "arrow - weak damage and health, quick attack, short reach");
    mvprintw(13, 0, "effect - attacks everyone, almost unkillable, binds effect to attackers");
    mvprintw(15, 0, "B for menu");
    mvprintw(16, 0, "Q to quit");
}

/**
 * updates the game
 * @param time - this will be passed to methods
 */
void Game::update(int time) {

    if (gameStatus == 3) {
        level->moveAndAttack(time);
        level->Attack(time);
        if (level->GetPassed() == 3) {
            this->endLevel();
            clear();
            mvprintw(0, 0, "You've won !");
            mvprintw(1, 0, "B to go back to menu");
            gameStatus = 2;
        }
    }
}

/**
 * Spawns attacker at certain door
 * @param in - at which door should attacker be spawned
 * @param name - name of attacker
 */
void Game::spawnAttacker(int in, const string & name) {
    if (level->GetMoney() > 1) {
        int x = in == 1 ? level->GetIn1()->x - 1 : level->GetIn2()->x - 1;
        int y = in == 1 ? level->GetIn1()->y : level->GetIn2()->y;
        loader->loadAttacker(level, name, x, y, attackerNumber);
        attackerNumber++;
        level->drawTowersAndAttackers();
        level->SetMoney(level->GetMoney()-100);
        mvprintw(level->GetHeight() + 6, 0, "Finances = %d", level->GetMoney());
    } else {
        mvprintw(20, 0, "Not enough money");
    }
}

/**
 * saves game
 */
void Game::saveGame() {
    loader->saveGame(this->level);
}

/**
 * loads game and plays it
 */
void Game::loadGame() {
    clear();
    level = loader->loadGame();
    level->Draw();
    level->InitShortWays();
    level->drawTowersAndAttackers();
}

/**
 * initialization of towers
 * @param levelNumber - number of level for which are towers fetched
 */
void Game::initTowers(int levelNumber) {
    vector<int> arr = loader->loadNumberOfTurrets(levelNumber);
    for (int i = 0; i < arr[0]; i++) {
        loader->loadTower(level, "bombard", towerNumber);
        towerNumber++;
    }
    for (int i = 0; i < arr[1]; i++) {
        loader->loadTower(level, "arrow", towerNumber);
        towerNumber++;
    }
    for (int i = 0; i < arr[2]; i++) {
        loader->loadTower(level, "effect", towerNumber);
        towerNumber++;
    }
}

/**
 * initualization of level
 * @param levelNumber number of level
 * @param levelName file name with levels
 * @param wallName file name with walls
 * @return fully functional level
 */
Level* Game::initLevel(int levelNumber, const string& levelName, const string& wallName) {
    clear();
    level = loader->loadMap(levelNumber, levelName, wallName);
    level->Draw();
    level->InitShortWays();
    this->initTowers(levelNumber);
    level->buildTowers();
    level->drawTowersAndAttackers();
    return level;
}

/**
 * Ends level and frees memory
 */
void Game::endLevel() {
    attackerNumber = 0;
    delete level;
    level = NULL;
}
