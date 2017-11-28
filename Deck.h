#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include "Card.h"

class Deck {
    public:
        std::vector<Card *> cards;

        // when true, creates a deck containing every possible card
        Deck(bool isFullDeck = false); 
        void shuffle();
};

#endif
