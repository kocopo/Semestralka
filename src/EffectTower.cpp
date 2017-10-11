/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EffectTower.h"
#include "Attacker.h"
#include "Freeze.h"
#include "ShredArmor.h"
#include "Weaken.h"
#include <vector>
#include <map>
#include <memory>
#include <ncurses.h>
using namespace std;

/**
 * Handles applying effects
 * @param time which is passed to attacker
 */
void EffectTower::Attack(int time) {
    if (!effects.empty() && !attackers.empty()) {
        for (auto & attacker : attackers) {
            if (attacker.second->GetEffect() == "nothing") {

                unsigned int randomEffect = rand() % effects.size();
                attacker.second->SetTime(time);
                effects.at(randomEffect)->doEffect(attacker.second);

            }
        }
    }
}

/**
 * checks if targets are in range, if not deletes them from map
 */
void EffectTower::CheckTargetRange() {
    int ID = -1;
    for (auto & attacker : attackers) {

        if (ID != -1) {
            this->deleteTarget(ID);
            ID = -1;
        }

        if (attacker.second->GetHealth() < 1 || !this->checkRange(attacker.second->GetXPosition(), attacker.second->GetYPosition())) {
            ID = attacker.first;
        }
    }
    if (ID != -1) {
        attackers.erase(ID);
        this->deleteTarget(ID);
    }
}

/**
 * delets target
 * @param ID of target
 */
void EffectTower::deleteTarget(int ID) {
    attackers.erase(ID);
}

/**
 * Looks for targets
 * @param attacker which is checked
 */
void EffectTower::FindTarget(Attacker* attacker) {
    if (this->checkRange(attacker->GetXPosition(), attacker->GetYPosition())) {
        this->attackers.insert(make_pair(attacker->GetID(), attacker));
    }
}

/**
 * Adds effect to vector
 * @param duration of effect
 * @param effect to add
 */
void EffectTower::addEffect(int duration, const string& effect) {
    if (effect == "freeze") {
        this->effects.push_back(shared_ptr<Effect>(new Freeze(duration)));
    } else if (effect == "shredArmor") {
        this->effects.push_back(shared_ptr<Effect>(new ShredArmor(duration)));
    } else if (effect == "weaken") {
        this->effects.push_back(shared_ptr<Effect>(new Weaken(duration)));
    }
}

/**
 * finds and deletes certain attacker
 * @param ID of attacker
 */
void EffectTower::findAndDelete(int ID) {
    bool dlete = false;
    if (!attackers.empty()) {
        for (auto & attacker : attackers) {
            if (attacker.first == ID) {
                dlete = true;
                break;
            }
        }
        if (dlete) {
            deleteTarget(ID);
        }
    }
}
