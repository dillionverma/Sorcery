#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H
#include "Decorator.h"

class MagicFatigue: public Decorator {
    public:
        MagicFatigue(std::shared_ptr<Minion> minion);
        int getAC() const override;
};

#endif
