#ifndef ENRAGE_H
#define ENRAGE_H
#include "Decorator.h"

class Enrage: public Decorator {
    public:
        Enrage(std::shared_ptr<Minion> minion);
        int getAttack() const;
        int getDefence() const;
        void attackMinion(Minion &m);
        void attackPlayer(Player &p);
        card_template_t display() override;
};

#endif
