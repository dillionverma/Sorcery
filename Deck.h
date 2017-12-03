#ifndef DECK_H
#define DECK_H
#include "Card.h"

class Deck {
  public:
    std::vector<std::shared_ptr<Card>> cards;
    Deck(std::string deckfile = "default.deck"); 
    void shuffle();
};

#endif
