#ifndef DECORATOR_H
#define DECORATOR_H
#include "Component.h"

class Decorator: public Component {
    protected:
    Component *component;
    public:
    Decorator(Component *component);
//    virtual ~Decorator();
};

#endif
