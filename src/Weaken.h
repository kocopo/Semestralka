/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Weaken.h
 * Author: otakar
 *
 * Created on 29. května 2017, 21:36
 */

#ifndef WEAKEN_H
#define WEAKEN_H
#include "Effect.h"
#include "Attacker.h"

using namespace std;

class Weaken : public Effect {
public:

    /**
     * Weaken constructor
     * @param duration
     */
    Weaken(int duration) : Effect(duration) {

    }

    /**
     * Weakens enemy
     * @param attacker
     */
    void doEffect(Attacker* attacker) override {
        attacker->SetEffect("weaken");
        attacker->SetEffectDuration(this->duration);
        attacker->SetDamage(attacker->GetDamage() / 2);
    }


};

#endif /* WEAKEN_H */

