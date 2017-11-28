#ifndef SPELL_H
#define SPELL_H
#include <string>
#include "Card.h"

class Spell: public Card {
    
    public:
    Spell(std::string, int cost, std::string info); 
};

#endif
