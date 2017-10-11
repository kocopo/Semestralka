



#ifndef SHORTESTWAYS_H
#define SHORTESTWAYS_H

#include <vector>
#include <memory>
#include "Position.h"
#include "Attacker.h"
#include "Wall.h"
using namespace std;

class Level;

class ShortestWays {
public:
    ShortestWays(Level* level);
    vector<shared_ptr<Position>> GetShortestWay(int inX, int inY);

    /**
     * 
     * @return vector<shared_ptr<Position> > shortway 1
     */
    vector<shared_ptr<Position> > GetShortWayIn1() const {
        return shortWay1;
    }

        /**
     * 
     * @return vector<shared_ptr<Position> > shortway 2
     */
    vector<shared_ptr<Position> > GetShortWayIn2() const {
        return shortWay2;
    }


    Position * getNextPosition(Attacker *);
    Position * getNearestCorner(Attacker *);
    int isRelevant(Attacker*, Wall*);
private:
    Level* level;
    vector<shared_ptr<Position>> shortWay1;
    vector<shared_ptr<Position>> shortWay2;


};


#endif /* SHORTESTWAYS_H */

