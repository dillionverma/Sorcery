#ifndef MINION_H
#define MINION_H
#include <string>
#include "Card.h"
#include "Ability.h"

class Minion: public Card {
    int attack;
    int defence;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;
    
    public:
    Minion(std::string name, int cost, std::string info, int attack, 
        int defence, int abilityCost);
    void gainAtk(int amount);
    void gainDef(int amount);
    void display() override;
    int &getDef();
};

#endif
