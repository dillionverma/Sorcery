#ifndef SILENCE_H
#define SILENCE_H
#include "Decorator.h"

class Silence: public Decorator {
    public:
        Silence(std::shared_ptr<Minion> minion);
        void notify(Board &b, Player &p, int target = -1) override;
};

#endif
