/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Attacker.h"
#include <ncurses.h>
#include "Tower.h"
#include <memory>
#include <cmath>
#include <map>
#include <string>
using namespace std;

/**
 * Attacker Contructor
 * @param xPosition
 * @param yPosition
 * @param ID
 * @param damage
 * @param MovementSpeed
 * @param attackSpeed
 * @param health
 * @param armor
 * @param range
 */
Attacker::Attacker(int xPosition, int yPosition, int ID, int damage, int MovementSpeed,
        int attackSpeed, int health, int armor, int range) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->ID = ID;
    this->damage = damage;
    this->movSpeed = MovementSpeed;
    this->attSpeed = attackSpeed;
    this->health = health;
    this->armor = armor;
    this->range = range;
    this->effect = "nothing";
    this->canAttack = true;
    this->canMove = true;
    this->effectDuration = 0;
}

/**
 * Draws attacker to screen
 */
void Attacker::Draw() {
    mvprintw(yPosition, xPosition, "%c", Letter());
}

/**
 * handles Attackers attack
 * @param towers which attacker attacks
 */
void Attacker::Attack(map<int, shared_ptr<Tower>> towers) {
    for (auto& tower : towers) {
        if (this->CheckForRange(tower.second.get())) {
            tower.second->SetHealth(tower.second->GetHealth() - this->damage);
        }
    }
}

/**
 * Checks if tower is in range
 * @param tower which is getting checked
 * @return true if is in range, false otherwise
 */
bool Attacker::CheckForRange(Tower* tower) {
    return (abs(tower->GetXPosition() - this->GetXPosition()) < this->range &&
            abs(tower->GetYPosition() - this->GetYPosition()) < this->range);
}

/**
 * undos effect if it had any
 */
void Attacker::undoEffect() {

    if (effect == "freeze") {
        this->SetMovSpeed(this->GetMovSpeed() / 2);
    } else if (effect == "weaken") {
        this->SetDamage(this->GetDamage() * 2);
    } else if (effect == "shredArmor") {
        this->SetArmor(this->GetArmor() * 2);
    }

    this->SetEffect("nothing");
    this->SetEffectDuration(0);
}
