#ifndef SPELL_H
#define SPELL_H
#include <string>
#include "Card.h"

class Spell: public Card {
    
    void playCard() override;

    public:
    Spell(std::string, int cost, std::string info); 
};

#endif
