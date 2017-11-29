#ifndef SPELL_H
#define SPELL_H
#include <string>
#include "Card.h"

class Board; class Player;

class Spell: public Card {
    
    public:
        Spell(std::string, int cost, std::string info); 
        void notify(Board &b, Player &p) override;
};

#endif
