#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Card.h"

class Board; class Player;

// enchantment will be a decorator
class Enchantment: public Card { 
    
    public:
      Enchantment(std::string name, int action, std::string info);
      card_template_t display() override;
      void notify(Board &b, Player &p, int target = -1) override;
};

#endif
