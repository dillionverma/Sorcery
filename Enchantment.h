#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Deck.h"
#include "Player.h"
#include "Card.h"

class Board; class Player;

// enchantment will be a decorator
class Enchantment: public Card { 
    public:
      Enchantment(std::string name, int action, std::string info);
      void display() override;
      void notify(Board &b, Player &p, int target = -1) override;
      void effect(Board &b, Player &p, int target = -1);
};

#endif
