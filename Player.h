#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"

class Player {
    std::string name;
    int health = 20;
    int mana = 3;
    // Board board;
    Deck deck;
    std::vector<Card *> hand;
    std::vector<Card *> grave;

    public:
    Player(std::string name);
    void shuffleDeck(std::vector<Card *> deck);
    void drawFromDeck();
    //void updateHealth(int newHealth);
    //void updateMana(int newMana);
};

#endif
