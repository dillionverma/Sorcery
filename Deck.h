#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include <memory>
#include "Card.h"

class Deck {
  public:
    std::vector<std::shared_ptr<Card>> cards;

    // when true, creates a deck containing every possible card
    Deck(std::string deckfile); 
    void shuffle();
};

#endif
