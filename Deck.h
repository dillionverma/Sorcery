#ifndef DECK_H
#define DECK_H
#include <memory>
#include <vector>

class Card;

class Deck {
  public:
    std::vector<std::shared_ptr<Card>> cards;
    Deck(std::string deckfile = "default.deck"); 
    std::shared_ptr<Card> loadCard(std::string cardName); 
    void shuffle();
};

#endif
