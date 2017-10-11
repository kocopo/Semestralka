

/* 
 * File:   Attacker.h
 * Author: Otakar Kočka
 *
 * Created on 2. května 2017, 19:06
 */

#ifndef ATTACKER_H
#define ATTACKER_H

#include <cstring>
#include <map>
#include <memory>
#include <string>

class Tower;

using namespace std;

class Attacker {
public:

    Attacker(int xPosition, int yPosition, int ID, int damage, int MovementSpeed, int attackSpeed, int health, int armor, int range);

    /**
     * 
     * @return Xposition 
     */
    int GetXPosition() const {
        return xPosition;
    }

    /**
     * SETS X POSITION
     * @param xPosition
     */
    void SetXPosition(int xPosition) {
        this->xPosition = xPosition;
    }

    /**
     * 
     * @return y position
     */
    int GetYPosition() const {
        return yPosition;
    }

    /**
     * 
     * @return ID of attacker
     */
    int GetID() const {
        return ID;
    }

    /**
     * sets y Position
     * @param yPosition
     */
    void SetYPosition(int yPosition) {
        this->yPosition = yPosition;
    }

    /**
     * 
     * @return letter of attacker 
     */
    char Letter() const {
        return '@';
    }

    /**
     * 
     * @return true - can, false - cant 
     */
    bool GetCanMove() const {
        return canMove;
    }

    /**
     * 
     * @return true - can, false - cant 
     */
    bool IsCanAttack() const {
        return canAttack;
    }

    /**
     * switches if can attack
     */
    void switchCanAttack() {
        canAttack = !canAttack;
    }

    /**
     * switches if can move
     */
    void switchCanMove() {
        canMove = !canMove;
    }
    void Draw();

        /**
     * sets health
     * @param health
     */
    void SetHealth(int health) {
        this->health = health;
    }

        /**
     * 
     * @return health 
     */
    int GetHealth() const {
        return health;
    }

        /**
     * 
     * @return Movement speed 
     */
    int GetMovSpeed() const {
        return movSpeed;
    }

    /**
     * 
     * @return attack speed
     */
    int GetAttSpeed() const {
        return attSpeed;
    }

        /**
     * 
     * @return armor 
     */
    int GetArmor() const {
        return armor;
    }
    void Attack(map<int, shared_ptr<Tower>>);

    /**
     * Sets armor
     * @param armor
     */
    void SetArmor(int armor) {
        this->armor = armor;
    }

        /**
     * sets damage
     * @param damage
     */
    void SetDamage(int damage) {
        this->damage = damage;
    }

        /**
     * sets movement speed
     * @param movSpeed
     */
    void SetMovSpeed(int movSpeed) {
        this->movSpeed = movSpeed;
    }

        /**
     * 
     * @return damage
     */
    int GetDamage() const {
        return damage;
    }

    /**
     * 
     * @return string with effect 
     */
    string GetEffect() const {
        return effect;
    }

        /**
     * sets effect
     * @param effect which is to be set
     */
    void SetEffect(const string & effect) {
        this->effect = effect;
    }

        /**
     * 
     * @return effect duration 
     */
    int GetEffectDuration() const {
        return effectDuration;
    }

        /**
     * 
     * @return time 
     */
    int GetTime() const {
        return time;
    }

        /**
     * sets time
     * @param time
     */
    void SetTime(int time) {
        this->time = time;
    }

        /**
     * sets effect duration
     * @param effectDuration
     */
    void SetEffectDuration(int effectDuration) {
        this->effectDuration = effectDuration;
    }
    void undoEffect();

        /**
     * 
     * @return range
     */
    int GetRange() const {
        return range;
    }


private:

    bool CheckForRange(Tower * tower);
    int damage,
    movSpeed,
    attSpeed,
    range,
    armor,
    health,
    ID,
    xPosition,
    yPosition;
    bool canMove , canAttack ;
    string effect;
    int effectDuration ;
    int time;
};

#endif /* ATTACKER_H */

