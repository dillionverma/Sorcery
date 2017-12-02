#ifndef IMAGE_H
#define IMAGE_H
#include "Board.h"
#include "Player.h"

class Component {
    public:
    virtual void effect(Board &b, Player &p, int target = -1) = 0;
};

#endif
