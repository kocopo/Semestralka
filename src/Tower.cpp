/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tower.h"
#include "Attacker.h"
#include <ncurses.h>
#include <cmath>
using namespace std;

/**
 * Tower Constructor
 * @param ID
 * @param damage
 * @param attacakSpeed
 * @param reach
 * @param health
 */
Tower::Tower(int ID, int damage, int attacakSpeed, int reach, int health) {
    this->target = NULL;
    this->ID = ID;
    this->damage = damage;
    this->attackSpeed = attacakSpeed;
    this->reach = reach;
    this->health = health;
}

/**
 * tower constructor
 * @param x
 * @param y
 * @param ID
 * @param damage
 * @param attacakSpeed
 * @param reach
 * @param health
 */
Tower::Tower(int x, int y, int ID, int damage, int attacakSpeed, int reach, int health) {
    this->xPosition = x;
    this->yPosition = y;
    this->target = NULL;
    this->ID = ID;
    this->damage = damage;
    this->attackSpeed = attacakSpeed;
    this->reach = reach;
    this->health = health;
}

/**
 * checks if target is wanted
 * @param ID of target
 */
void Tower::findAndDelete(int ID) {
    if (this->target != NULL) {
        if (ID == this->target->GetID())deleteTarget(ID);
    }
}

/**
 * Prints Tower into window
 */
void Tower::Draw() {
    mvprintw(this->yPosition, this->xPosition, "%c", this->getLetter());
}

/**
 * checks range of attacker 
 * @param x of attacker
 * @param y of attacker
 * @return true if is in range, false otherwise
 */
bool Tower::checkRange(int x, int y) {
    return (abs(x - this->xPosition) < this->reach && abs(y - this->yPosition) < this->reach);
}

/**
 * finds target if it hasnt got any
 * @param attacker
 */
void Tower::FindTarget(Attacker* attacker) {
    if (checkRange(attacker->GetXPosition(), attacker->GetYPosition())
            && this->target == NULL) {
        this->target = attacker;
    }
}

/**
 * check if current target is in range
 */
void Tower::CheckTargetRange() {
    if (this->target != NULL) {
        if (this->target->GetHealth() < 1 || !this->checkRange(this->target->GetXPosition(), this->target->GetYPosition())) {
            this->deleteTarget(this->target->GetID());
        }
    }
}

/**
 * deletes target
 * @param ID
 */
void Tower::deleteTarget(int ID) {
    this->target = NULL;
}

/**
 * handles attack
 * @param time for children
 */
void Tower::Attack(int time) {

    if (this->target != NULL) {
        int damage = this->damage - this->target->GetArmor();
        if (damage < 0)damage = 0;
        this->target->SetHealth(this->target->GetHealth() - damage);
    }
}
