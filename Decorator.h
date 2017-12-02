#ifndef DECORATOR_H
#define DECORATOR_H
#include "Minion.h"

class Decorator: public Minion {
    protected:
        std::shared_ptr<Minion> minion;
    public:
        Decorator(std::shared_ptr<Minion> minion);
        virtual ~Decorator()=0;
};

#endif
