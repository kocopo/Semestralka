/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EffectTower.h
 * Author: otakar
 *
 * Created on 21. května 2017, 23:31
 */

#ifndef EFFECTTOWER_H
#define EFFECTTOWER_H
#include "Tower.h"
#include "Effect.h"
#include <vector>
#include <memory>
#include <map>

using namespace std;

class EffectTower : public Tower {
public:

    /**
     * Effect tower constructor
     * @param ID
     * @param damage
     * @param attackSpeed
     * @param reach
     * @param health
     */
    EffectTower(int ID, int damage, int attackSpeed, int reach, int health)
    : Tower(ID, damage, attackSpeed, reach, health) {
        this->addEffect(3500, "freeze");
        this->addEffect(2500, "weaken");
        this->addEffect(3000, "shredArmor");

    }

    /**
     * Effect tower Constructor
     * @param x
     * @param y
     * @param ID
     * @param damage
     * @param attackSpeed
     * @param reach
     * @param health
     */
    EffectTower(int x, int y, int ID, int damage, int attackSpeed, int reach, int health)
    : Tower(x, y, ID, damage, attackSpeed, reach, health) {
        this->addEffect(3500, "freeze");
        this->addEffect(2500, "weaken");
        this->addEffect(3000, "shredArmor");

    }

    /**
     * 
     * @return letter of tower
     */
    char getLetter() override {
        return 'E';
    }
    void Attack(int time) override;
    void findAndDelete(int ID) override;
    void FindTarget(Attacker* attacker) override;
    void CheckTargetRange() override;
    void deleteTarget(int ID) override;
    void addEffect(int duration, const string & effect);

private:
    map<int, Attacker*> attackers;
    vector<shared_ptr<Effect>> effects;
};


#endif /* EFFECTTOWER_H */

