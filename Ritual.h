#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "Card.h"
#include "State.h"

class Player; class Board;

class Ritual: public Card {

    int numCharges;
    int activationCost;
    
    public:
        Ritual(std::string name, int cost, std::string info, int numCharges, int activationCost);
        void notify(Board &b, Player &p) override;
        void effect(Board &b, Player &p);
};
#endif
