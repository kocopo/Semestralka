/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Freeze.h
 * Author: otakar
 *
 * Created on 29. května 2017, 20:59
 */

#ifndef FREEZE_H
#define FREEZE_H
#include "Effect.h"
#include "Attacker.h"

using namespace std;

class Freeze : public Effect {
public:

    /**
     * Freeze constructor
     * @param duration
     */
    Freeze(int duration) : Effect(duration) {
    }

    /**
     * Freezes target
     * @param attacker
     */
    void doEffect(Attacker* attacker) override {
        attacker->SetEffect("freeze");
        attacker->SetEffectDuration(this->duration);
        attacker->SetMovSpeed(attacker->GetMovSpeed() * 2);
    }


};


#endif /* FREEZE_H */

