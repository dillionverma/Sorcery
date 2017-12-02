#ifndef HASTE_H
#define HASTE_H
#include "Decorator.h"
#include "Component.h"

class Haste: public Decorator {
    Component *comp;
    public:
    Haste(Component *component);
    void effect(Board &b, Player &p, int target = -1);
};

#endif
