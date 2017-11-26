#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "Card.h"

class Ritual: public Card {
    int numCharges;
    int activationCost;

    public:
    Ritual(std::string name, int cost, std::string info, Card::Location location,
        int numCharges, int activationCost);

    void playCard() override;
};

#endif
