/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Effect.h
 * Author: otakar
 *
 * Created on 17. května 2017, 0:20
 */

#ifndef EFFECT_H
#define EFFECT_H

#include "Attacker.h"
using namespace std;

class Effect {
public:

    /**
     * Effect constructor
     * @param duration of effect
     */
    Effect(int duration);
    /**
     * does effect to attacker
     * @param attacker
     */
    virtual void doEffect(Attacker * attacker) = 0;

    /**
     * 
     * @return duration of effects
     */
    int getDuration() const;

protected:
    int duration;
};


#endif /* EFFECT_H */

