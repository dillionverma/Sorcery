#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Card.h"

// enchantment will be a decorator
class Enchantment: public Card { 
    int effect; // only int for now for skeleton, until implemented
    
    public:
    Enchantment(std::string name, int action, std::string info, Card::Location location);
    void playCard() override;
};

#endif
