#ifndef GIANTSTRENGTH_H
#define GIANTSTRENGTH_H
#include "Decorator.h"

class GiantStrength: public Decorator {
    public:
        GiantStrength(std::shared_ptr<Minion> minion);
        int getAttack() const;
        int getDefence() const;
        void attackMinion(Minion &m);
        void attackPlayer(Player &p);
        card_template_t display();
};

#endif
