/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Position.h
 * Author: otakar
 *
 * Created on 6. května 2017, 22:24
 */

#ifndef POSITION_H
#define POSITION_H

class Position {
public:

    /**
     * Position Constructor
     * @param x
     * @param y
     */
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    /**
     * 
     * @param rhs
     * @return true if x and y equals right, false otherwise 
     */
    bool operator==(const Position & rhs) const {
        return (this->y == rhs.y && this->x == rhs.x);
    }

    int x, y;
};

#endif /* POSITION_H */

