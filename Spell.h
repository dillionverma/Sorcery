#ifndef SPELL_H
#define SPELL_H
#include <string>
#include "Player.h"
#include "Board.h"
#include "Card.h"
#include "Minion.h"
#include "Ritual.h"

class Spell: public Card {
    
    public:
    Spell(std::string, int cost, std::string info); 
    // when target = -1, then the card is the type with no target
    //      otherwise, tagret represents which card to play spell
    //      on in opponents hand. Where 1-5 are opponent cards
    //      and 0 is the ritual owned by player p
    void notify (Board &b, Player &p, int target = -1) override;
    void effect(Board &b, Player &p, int target = -1);
    card_template_t display() override;
};

#endif
