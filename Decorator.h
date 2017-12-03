#ifndef DECORATOR_H
#define DECORATOR_H
#include "Minion.h"

class Decorator: public Minion {
    protected:
        std::shared_ptr<Minion> minion;
    public:
        Decorator(std::shared_ptr<Minion> minion);
        virtual card_template_t display() override;
        virtual void changeAttack(const int amount) override;
        virtual void changeDefence(const int amount) override;
        virtual void changeAC(const int amount) override; 
        virtual int getAttack() const override;
        virtual int getDefence() const override;
        virtual int getAC() const override;
        virtual std::string getName() const;
        virtual int getCost() const;
        virtual void attackMinion(Minion &m) override;
        virtual void attackPlayer(Player &p) override;
};

#endif
