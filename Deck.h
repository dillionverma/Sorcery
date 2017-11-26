#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include "Card.h"

class Deck {
    public:
    std::vector<Card> cards;
    Deck(); 
    void shuffle();
};

#endif
