#ifndef GIANTSTRENGTH_H
#define GIANTSTRENGTH_H
#include "Decorator.h"
#include "Component.h"

class GiantStrength: public Decorator {
    Component *comp;
    public:
    GiantStrength(Component *component);
    void effect(Board &b, Player &p, int target = -1);
};

#endif
