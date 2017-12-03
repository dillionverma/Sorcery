#ifndef HASTE_H
#define HASTE_H
#include "Decorator.h"

class Haste: public Decorator {
    public:
        Haste(std::shared_ptr<Minion> minion);
        int getAction() const override;
};

#endif
