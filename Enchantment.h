#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include "Decorator.h"
#include "Component.h"

class Board; class Player;

class Enchantment: public Card, public Component { 
    public:
      Enchantment(std::string name, int action, std::string info);
      card_template_t display() override;
      void notify(Board &b, Player &p, int target = -1) override;
      void effect(Board &b, Player &p, int target = -1);
};

#endif
