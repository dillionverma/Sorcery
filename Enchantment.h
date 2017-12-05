#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Card.h"

class Board; class Player;

class Enchantment: public Card { 
    int attack;
    int defence;
    public:
      Enchantment(std::string name, int action, std::string info, int attack=0, int defence=0);
      card_template_t display() override;
      void notify(Board &b, Player &p, int target = -1) override;
      int getAttack() const;
      int getDefence() const;
};

#endif
