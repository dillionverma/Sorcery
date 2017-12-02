#ifndef SILENCE_H
#define SILENCE_H
#include "Decorator.h"
#include "Component.h"

class Silence: public Decorator {
    Component *comp;
    public:
    Silence(Component *component); 
    void effect(Board &b, Player &p, int target = -1);
};

#endif
