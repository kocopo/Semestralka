/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tower.h
 * Author: otakar
 *
 * Created on 2. května 2017, 19:06
 */

#ifndef TOWER_H
#define TOWER_H

class Attacker;

class Tower {
public:

    Tower(int ID, int damage, int attacakSpeed, int reach, int health);
    Tower(int x, int y, int ID, int damage, int attacakSpeed, int reach, int health);

    /**
     * 
     *  @return int attack speed
     */
    int GetAttackSpeed() const {
        return attackSpeed;
    }

    /**
     * 
     * @return int damage
     */
    int GetDamage() const {
        return damage;
    }

    /**
     * virtual function
     * @return char letter of tower
     */
    virtual char getLetter() {
        return 'I';
    }

    /**
     * 
     * @return int ID of tower
     */
    int GetID() const {
        return ID;
    }

    /**
     * 
     * @return int health 
     */
    int GetHealth() const {
        return health;
    }

    /**
     * 
     * @return int reach 
     */
    int GetReach() const {
        return reach;
    }

    /**
     * 
     * @return int x position
     */
    int GetXPosition() const {
        return xPosition;
    }

    /**
     * 
     * @return int y position
     */
    int GetYPosition() const {
        return yPosition;
    }

    /**
     * Sets health
     * @param health
     */
    void SetHealth(int health) {
        this->health = health;
    }

    /**
     * 
     * @return true - can, false - cant
     */
    bool GetCanAttack() const {
        return canAttack;
    }

    /**
     * switches if can attack
     */
    void switchCanAttack() {
        canAttack = !canAttack;
    }

    /**
     * sets x position
     * @param xPosition
     */
    void SetXPosition(int xPosition) {
        this->xPosition = xPosition;
    }

    /**
     * sets y position
     * @param yPosition
     */

    void SetYPosition(int yPosition) {
        this->yPosition = yPosition;
    }
    virtual void findAndDelete(int ID);
    virtual void deleteTarget(int ID);
    virtual void Attack(int time);
    void Draw();
    virtual void FindTarget(Attacker * attacker);
    virtual void CheckTargetRange();
protected:
    bool checkRange(int x, int y);

    int reach,
            health,
            damage,
            attackSpeed,
            xPosition = 0,
            yPosition = 0,
            ID;

    bool canAttack = true;
private:
    Attacker * target;
};

#endif /* TOWER_H */

