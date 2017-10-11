/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ShortestWays.h"
#include <vector>
#include <ncurses.h>
#include <memory>
#include <iostream>
#include "Level.h"
#include "Position.h"
#include "Attacker.h"
#include "Wall.h"

using namespace std;

/**
 * ShortestWay constructor
 * @param level
 */
ShortestWays::ShortestWays(Level* level) {
    this->level = level;
    this->shortWay1 = this->GetShortestWay(level->GetIn1()->x, level->GetIn1()->y);
    this->shortWay2 = this->GetShortestWay(level->GetIn2()->x, level->GetIn2()->y);
}

/**
 * Gets shorstest ways from door
 * @param inX
 * @param inY
 * @return returns vector of sahred_ptr to Position with shortest way
 */
vector<shared_ptr<Position> > ShortestWays::GetShortestWay(int inX, int inY) {
    vector<shared_ptr<Position> > shortestWay;
    shared_ptr<Attacker> inviAttacker = shared_ptr<Attacker>(new Attacker(inX - 1, inY, 0, 1, 1, 1, 1, 1, 1));
    while (true) {
        shared_ptr<Position> tmpPos = shared_ptr<Position>(getNextPosition(inviAttacker.get()));

        if (mvinch(tmpPos->y, tmpPos->x) == '=')break;

        if (mvinch(tmpPos->y, tmpPos->x) == '.') {
            inviAttacker->SetXPosition(tmpPos->x);
        } else {
            tmpPos->x = inviAttacker->GetXPosition();
        }
        //        cout << tmpPos->x << " - " << tmpPos->y << endl;
        inviAttacker->SetYPosition(tmpPos->y);
        shortestWay.push_back(tmpPos);
        //        break;
    }
    return shortestWay;

}

/**
 * gets next position for attacker
 * @param attacker
 * @return next position
 */
Position* ShortestWays::getNextPosition(Attacker * attacker) {
    int x, y;

    shared_ptr<Position> nearestCorner = shared_ptr<Position>(getNearestCorner(attacker));

    if (nearestCorner->y - 1 < attacker->GetYPosition()) {
        y = attacker->GetYPosition() - 1;
    } else if (nearestCorner->y - 1 > attacker->GetYPosition()) {
        y = attacker->GetYPosition() + 1;
    } else {
        y = attacker->GetYPosition();
    }

    if (nearestCorner->x < attacker->GetXPosition()) {
        x = attacker->GetXPosition() - 1;
    } else {
        x = attacker->GetXPosition();
    }
    return new Position(x, y);
}

/**
 * Finds nearest corner relative to attacker
 * @param att
 * @return nearest corner
 */
Position* ShortestWays::getNearestCorner(Attacker * att) {
    int x = 10000, y = 10000;
    for (shared_ptr<Wall> wall : this->level->GetWalls()) {
        int corner = isRelevant(att, wall.get());
        if (corner == 0) {
            continue;
        } else if (corner == 1) {

            if (abs(wall->GetLeftUpperCornerY() - att->GetYPosition()) <= y) {

                y = wall->GetLeftUpperCornerY();

            }
        } else if (corner == 2) {

            if (abs(wall->GetRightBottomCornerY() - att->GetYPosition()) <= y) {
                y = wall->GetRightBottomCornerY() + 2;
            }
        }
        if (att->GetXPosition() - wall->GetLeftUpperCornerX() < x) {
            x = wall->GetLeftUpperCornerX();

        }

    }

    if (x == 10000 || y == 10000) {
        return new Position(this->level->GetOut()->x, this->level->GetOut()->y + 1);
    }
    return new Position(x, y);
}

/**
 * Get if Wall is relevant in relation with attacker
 * @param attacker for whom we want to know if wall s relevant 
 * @param wall we are checking for relevance
 * @return  0 - not relevant, 1 - upper corner relevant, 2 - bottom corner relevant
 */
int ShortestWays::isRelevant(Attacker* att, Wall* wall) {
    if (att->GetXPosition() <= wall->GetLeftUpperCornerX())return 0;

    if (wall->GetLeftUpperCornerY() != this->level->GetY() && wall->GetRightBottomCornerY() != this->level->GetY() + this->level->GetHeight()) {
        if (abs(att->GetYPosition() - wall->GetLeftUpperCornerY()) > abs(att->GetYPosition() - wall->GetRightBottomCornerY())) {
            for (shared_ptr<Wall> cWall : this->level->GetWalls()) {
                if (wall->GetLeftUpperCornerX() < cWall->GetLeftUpperCornerX() && att->GetXPosition() > cWall->GetLeftUpperCornerX()) {
                    return 0;
                }
            }
            return 2;
        } else {
            for (shared_ptr<Wall> cWall : this->level->GetWalls()) {
                if (wall->GetLeftUpperCornerX() < cWall->GetLeftUpperCornerX() && att->GetXPosition() > cWall->GetLeftUpperCornerX()) {
                    return 0;
                }
            }
            return 1;
        }
    }


    if (wall->GetLeftUpperCornerY() != this->level->GetY() && att->GetYPosition() >= wall->GetLeftUpperCornerY() - 1) {
        for (shared_ptr<Wall> cWall : this->level->GetWalls()) {
            if (wall->GetLeftUpperCornerX() < cWall->GetLeftUpperCornerX() && att->GetXPosition() > cWall->GetLeftUpperCornerX()) {
                return 0;
            }

        }
        return 1;
    } else if (wall->GetRightBottomCornerY() != this->level->GetY() + this->level->GetHeight() && att->GetYPosition() <= wall->GetRightBottomCornerY() + 1) {
        for (shared_ptr<Wall> cWall : this->level->GetWalls()) {
            if (wall->GetLeftUpperCornerX() < cWall->GetLeftUpperCornerX() && att->GetXPosition() > cWall->GetLeftUpperCornerX()) {
                return 0;
            }
        }
        return 2;
    } else {
        return 0;
    }
}