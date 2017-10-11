/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MapLoader.h"
#include "Level.h"
#include "Attacker.h"
#include "Wall.h"
#include "Tower.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <sstream>
#include <vector>
using namespace std;

/**
 * Loads map from file
 * @param levelNumber number of level
 * @param levelName file name with levels
 * @param wallsName file name with walls
 * @return level loaded from file
 */
Level* MapLoader::loadMap(int levelNumber, const string & levelName, const string & wallsName) {

    string line;
    ifstream file(levelName);
    Level * level;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == '/')continue;

            if (line == ("level" + to_string(levelNumber))) {
                while (getline(file, line)) {
                    if (line == ("level" + to_string(levelNumber + 1)))break;
                    if (line == "map") {
                        getline(file, line);
                        vector<int> arr;
                        int temp;
                        stringstream ss(line);
                        while (ss >> temp) {
                            arr.push_back(temp);
                        }
                        level = new Level(arr[1], arr[0], arr[3], arr[2]);
                    }
                    if (line == "ins") {
                        getline(file, line);
                        vector<int> arr;
                        int temp;
                        istringstream ss(line);
                        while (ss >> temp) {
                            arr.push_back(temp);
                        }
                        level->addIns(arr[0], arr[1], arr[2], arr[3]);
                    }
                    if (line == "outs") {
                        getline(file, line);
                        vector<int> arr;
                        int temp;
                        istringstream ss(line);
                        while (ss >> temp) {
                            arr.push_back(temp);
                        }
                        level->addOut(arr[0], arr[1]);
                    }
                }
            }
            if (line == ("level" + to_string(levelNumber + 1)))break;
        }
        this->loadWalls(level, levelNumber, wallsName);
        file.close();
    } else {
        mvprintw(2, 0, "There is no Save");
        return NULL;
    }
    return level;

}

/**
 * loads number of turrets for level
 * @param levelNumber
 * @return vector of ints witj tower numbers
 */
vector<int> MapLoader::loadNumberOfTurrets(int levelNumber) {
    string line;
    vector<int> arr;
    ifstream file("src/res/towerNumbers.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line == ("level" + to_string(levelNumber))) {
                getline(file, line);

                int temp;

                istringstream ss(line);
                while (ss >> temp) {
                    arr.push_back(temp);
                }
            }

        }
    }
    file.close();
    return arr;

}

/**
 * loads walls
 * @param level
 * @param levelNumber
 * @param wallsName
 */
void MapLoader::loadWalls(Level * level, int levelNumber, const string & wallsName) {
    string line;
    ifstream file(wallsName);
    if (file.is_open()) {
        while (getline(file, line)) {

            if (line == ("level" + to_string(levelNumber))) {
                while (getline(file, line)) {
                    if (line == ("level" + to_string(levelNumber + 1)))break;
                    vector<int> arr;
                    int temp;
                    istringstream ss(line);
                    while (ss >> temp) {
                        arr.push_back(temp);
                    }
                    level->addWall(arr[0], arr[1], arr[2], arr[3]);
                    arr.clear();
                }
            }
            if (line == ("level" + to_string(levelNumber + 1)))break;
        }
    }
    file.close();
}

/**
 * Loads attacker from file
 * @param level
 * @param attackerName
 * @param x
 * @param y
 * @param ID
 */

void MapLoader::loadAttacker(Level* level, const string& attackerName, int x, int y, int ID) {
    string line;
    ifstream file("src/res/attackers.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line == attackerName) {
                getline(file, line);

                vector<int> arr;
                int temp;

                istringstream ss(line);
                while (ss >> temp) {
                    arr.push_back(temp);
                }
                level->addAttacker(x, y, ID, arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
            }
        }
    }
    file.close();
}

/**
 * loads tower from file
 * @param level
 * @param towerName
 * @param ID
 */
void MapLoader::loadTower(Level* level, const string& towerName, int ID) {
    string line;
    ifstream file("src/res/towers.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line == towerName) {
                getline(file, line);

                vector<int> arr;
                int temp;

                istringstream ss(line);
                while (ss >> temp) {
                    arr.push_back(temp);
                }

                if (towerName == "effect") {
                    level->AddETower(ID, arr[0], arr[1], arr[2], arr[3]);
                } else {
                    level->addTower(ID, arr[0], arr[1], arr[2], arr[3]);
                }
                break;
            }
        }
    }
    file.close();
}

/**
 * saves game to file
 * @param level which is to be saved
 */
void MapLoader::saveGame(Level* level) {
    ofstream file;
    remove("src/res/mapsave.txt");
    remove("src/res/wallsave.txt");
    remove("src/res/attackersave.txt");
    remove("src/res/towersave.txt");
    string line;

    file.open("src/res/mapsave.txt");
    file << "level1\nmap\n";
    line = to_string(level->GetX()) + " " + to_string(level->GetY()) + " " + to_string(level->GetWidth()) + " "
            + to_string(level->GetHeight()) + "\n";
    file << line;
    file << "ins\n";
    line = to_string(level->GetIn1()->x) + " " + to_string(level->GetIn1()->y) + " " + to_string(level->GetIn2()->x)
            + " " + to_string(level->GetIn2()->y) + "\n";
    file << line;
    file << "outs\n";
    line = to_string(level->GetOut()->x) + " " + to_string(level->GetOut()->y) + "\n";
    file << line;
    file << "level2";
    file << "money\n" << to_string(level->GetMoney());

    file.close();


    file.open("src/res/wallsave.txt");
    file << "level1\n";
    for (shared_ptr<Wall> wall : level->GetWalls()) {
        line = to_string(wall->GetLeftUpperCornerY()) + " " + to_string(wall->GetLeftUpperCornerX()) + " " +
                to_string(wall->GetRightBottomCornerY()) + " " + to_string(wall->GetRigthBottomCornerX()) + "\n";
        file << line;
    }
    file << "level2";
    file.close();

    file.open("src/res/attackersave.txt");
    for (auto& attacker : level->GetAttackers()) {
        line = to_string(attacker.second->GetXPosition()) + " " + to_string(attacker.second->GetYPosition()) + " "
                + to_string(attacker.first) + " " + to_string(attacker.second->GetDamage()) + " " + to_string(attacker.second->GetMovSpeed()) + " "
                + to_string(attacker.second->GetAttSpeed()) + " " + to_string(attacker.second->GetHealth()) + " " + to_string(attacker.second->GetArmor()) + " "
                + to_string(attacker.second->GetRange()) + "\n";
        file << line;
    }
    file.close();

    file.open("src/res/towersave.txt");
    for (auto & tower : level->GetTowers()) {
        file << tower.second->getLetter() << "\n";
        line = to_string(tower.second->GetXPosition()) + " " + to_string(tower.second->GetYPosition()) + " "
                + to_string(tower.first) + " " + to_string(tower.second->GetDamage()) + " "
                + to_string(tower.second->GetAttackSpeed()) + " " + to_string(tower.second->GetReach()) + " "
                + to_string(tower.second->GetHealth()) + "\n";
        file << line;
    }
    file.close();
}

/**
 * loads game
 * @return loaded level
 */
Level* MapLoader::loadGame() {
    Level * level = this->loadMap(1, "src/res/mapsave.txt", "src/res/wallsave.txt");
    if (level == NULL) return NULL;
    string line;
    ifstream file("src/res/attackersave.txt");

    if (file.is_open()) {
        while (getline(file, line)) {

            vector<int> arr;
            int temp;

            istringstream ss(line);
            while (ss >> temp) {
                arr.push_back(temp);
            }
            level->addAttacker(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);
        }
    }
    file.close();

    file.open("src/res/towersave.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            string towerType = line == "E" ? "effect" : "normal";
            getline(file, line);
            vector<int> arr;
            int temp;

            istringstream ss(line);
            while (ss >> temp) {
                arr.push_back(temp);
            }
            if (towerType == "effect") {
                level->AddETower(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
            } else {
                level->addTower(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
            }

        }
    }
    file.close();
    file.open("src/res/mapsave.txt");
    if(file.is_open()){
        while(getline(file,line)){
            if(line == "money"){
                getline(file,line);
                istringstream ss(line);
                int temp;
                ss >> temp;
                level->SetMoney(temp);
            }
        }
    }
    file.close();
    return level;
}
