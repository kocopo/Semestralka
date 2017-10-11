
/* 
 * File:   Wall.h
 * Author: otakar
 *
 * Created on 6. května 2017, 15:58
 */



#ifndef WALL_H
#define WALL_H

class Wall {
public:

    /**
     * Wall constructor
     * @param leftUpperCornerX
     * @param leftUpperCornerY
     * @param rightBottomCornerX
     * @param rightBottomCornerY
     */
    Wall(int leftUpperCornerX, int leftUpperCornerY, int rightBottomCornerX, int rightBottomCornerY) {
        this->leftUpperCornerX = leftUpperCornerX;
        this->leftUpperCornerY = leftUpperCornerY;
        this->rightBottomCornerY = rightBottomCornerY;
        this->rightBottomCornerX = rightBottomCornerX;

    }

    /**
     * 
     * @return int upper x position
     */
    int GetLeftUpperCornerX() const {
        return leftUpperCornerX;
    }

    /**
     * 
     * @return upper y position
     */
    int GetLeftUpperCornerY() const {
        return leftUpperCornerY;
    }

    /**
     * 
     * @return int bottom y position
     */
    int GetRightBottomCornerY() const {
        return rightBottomCornerY;
    }

    /**
     * 
     * @return int bottom x position
     */
    int GetRigthBottomCornerX() const {
        return rightBottomCornerX;
    }

private:
    int leftUpperCornerX, leftUpperCornerY, rightBottomCornerX, rightBottomCornerY;
};


#endif /* WALL_H */
