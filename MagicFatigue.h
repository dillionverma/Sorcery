#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H
#include "Decorator.h"
#include "Component.h"

class MagicFatigue: public Decorator {
    Component *comp;
    public:
    MagicFatigue(Component *component); 
    void effect(Board &b, Player &p, int target = -1);
};

#endif
