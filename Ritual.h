#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "Card.h"
#include "State.h"

class Player;

class Ritual: public Card {

    void virtual effect(Player &p)=0;

    protected:
        int numCharges;
        int activationCost;
    
    public:
        Ritual(std::string name, int cost, std::string info,
            int numCharges, int activationCost);
        void notify(Player &p);

};

// Concrete Ritual implementations:

class DarkRitual: public Ritual {
    void effect(Player &p) override;
    public:
        DarkRitual(std::string name, int cost, std::string info, int numCharges, int activationCost);
};

class AuraOfPower: public Ritual {
    void effect(Player &p) override;
    public:
        AuraOfPower(std::string name, int cost, std::string info, int numCharges, int activationCost);
};

class Standstill: public Ritual {
    void effect(Player &p) override;
    public:
        Standstill(std::string name, int cost, std::string info, int numCharges, int activationCost);
};

#endif
