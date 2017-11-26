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

    public:
    // ability to be changed in implementation after depending on how we choose to implement
    // only int rn for simplification of skeleton
    Minion(std::string name, int cost, std::string info, Card::Location location, int attack, 
        int defense, int abilityCost);
    void playCard() override;

};

#endif
