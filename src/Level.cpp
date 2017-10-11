#include "Level.h"
#include "Wall.h"
#include "Attacker.h"
#include "Tower.h"
#include "ShortestWays.h"
#include "EffectTower.h"
#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <vector>
#include <cmath>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace std::chrono;

/**
 * Level constructor
 * @param y position
 * @param x position
 * @param height
 * @param width
 */
Level::Level(int y, int x, int height, int width) {
    this->y = y;
    this->x = x;
    this->height = height;
    this->width = width;
}

/**
 * level destructor
 */
Level::~Level() {
    walls.clear();
    towers.clear();
    attackers.clear();
}

/**
 * deletes attacker by ID
 * @param ID of attacker
 */
void Level::deleteAttackerByID(int ID) {
    for (auto & tower : towers) {
        tower.second->findAndDelete(ID);
    }
    mvprintw(attackers[ID]->GetYPosition(), attackers[ID]->GetXPosition(), ".");
    this->attackers.erase(ID);

}

/**
 * dele tower by ID
 * @param ID of tower
 */
void Level::deleteTowerByID(int ID) {
    mvprintw(towers[ID]->GetYPosition(), towers[ID]->GetXPosition(), ".");
    this->towers.erase(ID);
}

/**
 * initializes short ways
 */
void Level::InitShortWays() {
    shortestWay = shared_ptr<ShortestWays>(new ShortestWays(this));
}

/**
 * Draws level
 */
void Level::Draw() {
    // draw top and bottom
    for (int i = x; i < width + x; i++) {
        mvprintw(y, i, "#"); //top
        mvprintw(y + height, i, "#"); //bottom
    }

    //draw insides and and left and right walls
    for (int i = y + 1; i < y + height; i++) {
        mvprintw(i, x, "#");
        mvprintw(i, x + width - 1, "#");
        for (int j = x + 1; j < width + x - 1; j++) {
            mvprintw(i, j, ".");
        }
    }

    if (!walls.empty()) {
        for (shared_ptr<Wall> wall : walls) {
            for (int i = wall->GetLeftUpperCornerX(); i <= wall->GetRigthBottomCornerX(); i++) {
                for (int j = wall->GetLeftUpperCornerY(); j <= wall->GetRightBottomCornerY(); j++) {
                    mvprintw(j, i, "#");
                }
            }

        }
    }
    //draw ins
    if (in1 != NULL) {
        mvprintw(in1->y, in1->x, "<");
        mvprintw(in1->y, in1->x + 1, "=");
        mvprintw(in1->y, in1->x + 2, "1");
    }
    if (in2 != NULL) {
        mvprintw(in2->y, in2->x, "<");
        mvprintw(in2->y, in2->x + 1, "=");
        mvprintw(in2->y, in2->x + 2, "2");
    }
    //    
    //draw out
    if (out != NULL) {
        mvprintw(out->y, out->x, "=");
        mvprintw(out->y, out->x - 1, "<");
    }


    mvprintw(this->height + 2, 0, "door 1 :     door 2 :");
    mvprintw(this->height + 3, 0, "a - orc      y - orc     w - save game");
    mvprintw(this->height + 4, 0, "s - goblin   x - goblin  b - back to menu");
    mvprintw(this->height + 5, 0, "d - wolf     c - wolf    q - quit");
    mvprintw(this->height + 6, 0, "Finances = %d", this->money);

}

/**
 * draws towers and attackers
 */
void Level::drawTowersAndAttackers() {
    if (!towers.empty()) {
        for (auto& tower : towers) {
            tower.second->Draw();
        }
    }

    if (!attackers.empty()) {
        for (auto& attacker : attackers) {
            attacker.second->Draw();
        }
    }
}

/**
 * adds wall
 * @param upperY walls upper y position
 * @param upperX walls upper x position
 * @param bottomY walls bottom y position
 * @param bottomX walls bottom x position
 */
void Level::addWall(int upperY, int upperX, int bottomY, int bottomX) {

    walls.push_back(shared_ptr<Wall>(new Wall(upperX, upperY, bottomX, bottomY)));

}

/**
 * Adds effect tower
 * @param ID
 * @param damage
 * @param attackSpeed
 * @param reach
 * @param health
 */
void Level::AddETower(int ID, int damage, int attackSpeed, int reach, int health) {
    towers.insert(make_pair(ID, shared_ptr<Tower>(new EffectTower(ID, damage, attackSpeed, reach, health))));
}

/**
 * adds effect tower
 * @param x
 * @param y
 * @param ID
 * @param damage
 * @param attackSpeed
 * @param reach
 * @param health
 */
void Level::AddETower(int x, int y, int ID, int damage, int attackSpeed, int reach, int health) {
    towers.insert(make_pair(ID, shared_ptr<Tower>(new EffectTower(x, y, ID, damage, attackSpeed, reach, health))));
}

/**
 * adds tower
 * @param ID
 * @param damage
 * @param attackSpeed
 * @param reach
 * @param health
 */
void Level::addTower(int ID, int damage, int attackSpeed, int reach, int health) {
    towers.insert(make_pair(ID, shared_ptr<Tower>(new Tower(ID, damage, attackSpeed, reach, health))));
}

/**
 * adds tower
 * @param x
 * @param y
 * @param ID
 * @param damage
 * @param attackSpeed
 * @param reach
 * @param health
 */
void Level::addTower(int x, int y, int ID, int damage, int attackSpeed, int reach, int health) {
    towers.insert(make_pair(ID, shared_ptr<Tower>(new Tower(x, y, ID, damage, attackSpeed, reach, health))));
}

/**
 * adds attacker
 * @param x
 * @param y
 * @param ID
 * @param damage
 * @param MovementSpeed
 * @param attackSpeed
 * @param health
 * @param armor
 * @param range
 */
void Level::addAttacker(int x, int y, int ID, int damage, int MovementSpeed,
        int attackSpeed, int health, int armor, int range) {
    attackers.insert(make_pair(ID, shared_ptr<Attacker>(new Attacker(x, y, ID, damage, MovementSpeed,
            attackSpeed, health, armor, range))));
}

/**
 * AI for building towers at random locations
 */
void Level::buildTowers() {
    int i = 0;
    for (auto & tower : towers) {

        this->findSpotForTower(tower.second.get(), i);
        i += 13;
    }
}

/**
 * finds free random spot for tower
 * @param tower to build
 * @param numberForRand number for random generator
 */
void Level::findSpotForTower(Tower* tower, int numberForRand) {

    srand(time(0) + numberForRand);

    int randomWay = rand() % 2;
    vector<shared_ptr < Position>> shortWay = randomWay == 0 ? this->shortestWay->GetShortWayIn1() : this->shortestWay->GetShortWayIn2();

    Position randPosition = *(shortWay.at(rand() % shortWay.size()).get());

    vector<Position> tmp;
    for (shared_ptr<Position> post : shortWay) {
        tmp.push_back(Position(post->x, post->y));
    }
    while (true) {
        Position position(randPosition.x + (rand() % 3) - 1, randPosition.y + (rand() % 3) - 1);
        vector<Position>::iterator it;
        it = find(tmp.begin(), tmp.end(), position);
        bool canBeBuild = true;
        if (it == tmp.end() && mvinch(position.y, position.x) == '.') {

            for (auto& twr : towers) {
                if (position.x == twr.second->GetXPosition() && position.y == twr.second->GetYPosition()) {
                    canBeBuild = false;
                    break;
                }
            }
            if (canBeBuild) {
                tower->SetXPosition(position.x);
                tower->SetYPosition(position.y);
                break;
            }
        }
    }

}

/**
 * handles attack of towers and attackers displays attackers hralth
 * @param ms time which is compared to current time
 */
void Level::Attack(int ms) {
    int deleteTowerID = -1, deleteAttackerID = -1;

    milliseconds now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());

    for (auto & attacker : attackers) {
        if (attacker.second->GetEffect() != "nothing") {
            if ((now.count() - attacker.second->GetTime()) >= attacker.second->GetEffectDuration()) {
                attacker.second->undoEffect();
            }
        }
        mvprintw(0, this->width + 4, "Attackers:");
        mvprintw(attacker.first + 1, this->width + 4, "%d - %d", attacker.first, attacker.second->GetHealth());
        if (attacker.second->GetEffect() != "nothing") {
            mvprintw(attacker.first + 1, this->width + 12, "%s", attacker.second->GetEffect().c_str());
        }
        if (deleteAttackerID != -1) {
            deleteAttackerByID(deleteAttackerID);
            deleteAttackerID = -1;
        }
        if (attacker.second->GetHealth() < 1) {

            deleteAttackerID = attacker.first;
            continue;
        }
        if ((now.count() - ms) % attacker.second->GetAttSpeed() <= 1 && attacker.second->IsCanAttack()) {
            attacker.second->Attack(this->GetTowers());
            attacker.second->switchCanAttack();
        }

        if ((now.count() - ms) % attacker.second->GetAttSpeed() > 1 && !attacker.second->IsCanAttack()) {
            attacker.second->switchCanAttack();
        }


        for (auto & tower : towers) {
            if (tower.second->GetHealth() < 1) {
                deleteTowerID = tower.first;
                continue;
            }

            if (deleteTowerID != -1) {
                deleteTowerByID(deleteTowerID);
                deleteTowerID = -1;
            }

            tower.second->CheckTargetRange();
            tower.second->FindTarget(attacker.second.get());

            if ((now.count() - ms) % tower.second->GetAttackSpeed() <= 1 && tower.second->GetCanAttack()) {

                tower.second->Attack(now.count());

                tower.second->switchCanAttack();
            }
            if ((now.count() - ms) % tower.second->GetAttackSpeed() > 1 && !tower.second->GetCanAttack()) {
                tower.second->switchCanAttack();
            }


        }
        if (deleteTowerID != -1) {
            deleteTowerByID(deleteTowerID);
            deleteTowerID = -1;
        }
        if (deleteAttackerID != -1) {
            continue;
        }

    }
    if (deleteAttackerID != -1) {
        this->deleteAttackerByID(deleteAttackerID);

    }
}

/**
 * handles movement of of attackers and attacking
 * @param ms time that is comapred with now
 */
void Level::moveAndAttack(int ms) {

    int deleteAttackerID = -1;

    milliseconds now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());



    for (auto& attacker : attackers) {


        if (deleteAttackerID != -1) {
            deleteAttackerByID(deleteAttackerID);
            deleteAttackerID = -1;
        }
        if ((now.count() - ms) % attacker.second->GetMovSpeed() <= 1 && attacker.second->GetCanMove()) {

            shared_ptr<Position> newPosition = shared_ptr<Position>(this->shortestWay->getNextPosition(attacker.second.get()));


            switch (mvinch(newPosition->y, newPosition->x)) {
                case '@':
                    continue;
                    break;
                case '=':
                    this->passed++;
                    deleteAttackerID = attacker.second->GetID();
                    continue;
                    break;
                case '.':
                    mvprintw(attacker.second->GetYPosition(), attacker.second->GetXPosition(), ".");
                    attacker.second->SetXPosition(newPosition->x);
                    break;
                default:
                    mvprintw(attacker.second->GetYPosition(), attacker.second->GetXPosition(), ".");
                    break;
            }

            attacker.second->SetYPosition(newPosition->y);

            mvprintw(attacker.second->GetYPosition(), attacker.second->GetXPosition(), "%c", attacker.second->Letter());
            attacker.second->switchCanMove();
        }
        if ((now.count() - ms) % attacker.second->GetMovSpeed() > 1 && !attacker.second->GetCanMove()) {
            attacker.second->switchCanMove();
        }

    }
    if (deleteAttackerID != -1) {
        deleteAttackerByID(deleteAttackerID);
        deleteAttackerID = -1;
    }

}


