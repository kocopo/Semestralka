/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Attacker.h"
#include "Effect.h"

Effect::Effect(int duration) {
    this->duration = duration;
}

int Effect::getDuration() const {
    return duration;
}
