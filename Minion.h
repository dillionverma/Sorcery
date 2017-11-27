#ifndef MINION_H
#define MINION_H
#include <string>
#include "Card.h"
#include "Ability.h"

class Minion: public Card {
    int attack;
    int defense;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;
    void playCard() override;
    
    public:
    Minion(std::string name, int cost, std::string info, int attack, 
        int defense, int abilityCost);

};

#endif
