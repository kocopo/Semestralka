
/* 
 * File:   Level.h
 * Author: otakar
 *
 * Created on 2. května 2017, 19:07
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "Wall.h"
#include "Attacker.h"
#include "Tower.h"
#include "Position.h"
#include <vector>
#include <chrono>
#include <memory>
#include <map>
using namespace std;
class ShortestWays;

class Level {
public:

    Level(int y,
            int x,
            int height,
            int width);
    ~Level();

    /**
     * 
     * @return int height
     */
    int GetHeight() const {
        return height;
    }

    /**
     * 
     *  @return int width
     */
    int GetWidth() const {
        return width;
    }

        /**
     * 
     * @return int x position
     */
    int GetX() const {
        return x;
    }

    /**
     * 
     * @return int y position
     */
    int GetY() const {

        return y;
    }
    void FindShortestWay();
    void moveAndAttack(int ms);
    void Attack(int ms);
    void Draw();
    void InitShortWays();
    void addWall(int upperY, int upperX, int bottomY, int bottomX);
    void addAttacker(int x, int y, int ID, int damage, int MovementSpeed,
            int attackSpeed, int health, int armor, int range);
    void addTower(int ID, int damage, int attackSpeed, int reach, int health);
    void addTower(int x, int y, int ID, int damage, int attackSpeed, int reach, int health);
    void deleteAttackerByID(int);
    void deleteTowerByID(int);
    void AddETower(int ID, int damage, int attackSpeed, int reach, int health);
    void AddETower(int x, int y, int ID, int damage, int attackSpeed, int reach, int health);

    /**
     * adds doors to level
     * @param x1 door 1 x
     * @param y1 door 1 y 
     * @param x2 door 2 x
     * @param y2 door 2 y
     */
    void addIns(int x1, int y1, int x2, int y2) {
        in1 = shared_ptr<Position>(new Position(x1, y1));
        in2 = shared_ptr<Position>(new Position(x2, y2));
    }

    /**
     * adds out door
     * @param x
     * @param y
     */
    void addOut(int x, int y) {
        out = shared_ptr<Position>(new Position(x, y));
    }

    /**
     * 
     * @return Position door 1 
     */
    shared_ptr<Position> GetIn1() const {
        return in1;
    }

    /**
     * 
     * @return Position door 2
     */
    shared_ptr<Position> GetIn2() const {
        return in2;
    }

    /**
     * 
     * @return map<int,shared_ptr<Attacker> > attackers
     */
    map<int, shared_ptr<Attacker> > GetAttackers() const {
        return attackers;
    }

    /**
     * @return Position out door
     */
    shared_ptr<Position> GetOut() const {
        return out;
    }

    /**
     * 
     * @return map<int,shared_ptr<Tower>> of towers
     */
    map<int, shared_ptr<Tower>> GetTowers() const {
        return towers;
    }

    /**
     * 
     * @return vector of walls
     */
    vector<shared_ptr<Wall> > GetWalls() const {
        return walls;
    }

    /**
     * 
     * @return int howe many attackers passed
     */
    int GetPassed() const {
        return passed;
    }
    /**
     * 
     * @return int money 
     */
    int GetMoney() const {
        return money;
    }
    /**
     * sets money
     * @param money
     */
    void SetMoney(int money) {
        this->money = money;
    }


    void drawTowersAndAttackers();
    void buildTowers();
private:

    int passed = 0;
    void findSpotForTower(Tower * tower, int numberForRand);
    void printSW();
    Position * getNextPosition(Attacker *);
    Position * getNearestCorner(Attacker *);
    int isRelevant(Attacker*, Wall*);
    int x, y, height, width, money = 1000;
    map<int, shared_ptr<Tower>> towers;
    map<int, shared_ptr<Attacker>> attackers;
    vector<shared_ptr<Wall>> walls;
    shared_ptr<Position> in1;
    shared_ptr<Position> in2;
    shared_ptr<Position> out;
    shared_ptr<ShortestWays> shortestWay;
};
//

#endif /* LEVEL_H */

