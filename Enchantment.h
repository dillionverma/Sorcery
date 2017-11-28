#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <string>
#include "Card.h"

// enchantment will be a decorator
class Enchantment: public Card { 
    
    public:
    Enchantment(std::string name, int action, std::string info);

};

#endif
