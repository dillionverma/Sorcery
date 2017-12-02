#ifndef ENRAGE_H
#define ENRAGE_H
#include "Decorator.h"
#include "Component.h"

class Enrage: public Decorator {
    Component *comp;
    public:
    Enrage(Component *component);
    virtual void effect(Board &b, Player &p, int effect = -1);
};

#endif
