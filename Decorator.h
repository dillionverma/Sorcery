#ifndef DECORATOR_H
#define DECORATOR_H
#include "Minion.h"
#include "Player.h"

class Decorator: public Minion {
    protected:
        std::shared_ptr<Minion> minion;
    public:
        Decorator(std::shared_ptr<Minion> minion);
        card_template_t display() override;
        void changeAttack(const int amount) override;
        void changeDefence(const int amount) override;
        void changeAC(const int amount) override; 
        int getAttack() const override;
        int getDefence() const override;
        int getAC() const override;
        std::string getName() const;
        int getCost() const;
        void attackMinion(Minion &m) override;
        void attackPlayer(Player &p) override;
        void notify(Board &b, Player &p, int target = -1) override;
};

#endif
