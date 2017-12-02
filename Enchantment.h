#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Deck.h"
#include "Player.h"
#include "Card.h"

class Board; class Player;

class Enchantment: public Card { 
    public:
      Enchantment(std::string name, int action, std::string info);
      card_template_t display() override;
      virtual void notify(Board &b, Player &p, int target = -1) override;
};

#endif
