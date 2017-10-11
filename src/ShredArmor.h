/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShredArrmor.h
 * Author: otakar
 *
 * Created on 29. května 2017, 21:37
 */

#ifndef SHREDARRMOR_H
#define SHREDARRMOR_H
#include "Effect.h"
#include "Attacker.h"

using namespace std;

class ShredArmor : public Effect {
public:

    /**
     * ShredArmor constructor
     * @param duration
     */
    ShredArmor(int duration) : Effect(duration) {
    }

    /**
     * shreds armor of attacker
     * @param attacker
     */
    void doEffect(Attacker* attacker) {
        attacker->SetEffect("shredArmor");
        attacker->SetEffectDuration(this->duration);
        attacker->SetArmor(attacker->GetArmor() / 2);
    }
};

#endif /* SHREDARRMOR_H */

