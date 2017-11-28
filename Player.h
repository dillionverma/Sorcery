#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "State.h"
#include "Board.h"
#include "Minion.h"

class Player {
    std::string name;
    int health = 20;
    int mana = 3;
    int side;
    State state;
    Deck deck = Deck();
    std::vector<Card *> hand;
    std::vector<Minion> grave;

    public:
        Player(std::string name, int side);
        void shuffleDeck(std::vector<Card *> deck);
        void drawFromDeck();
        void gainHealth(int amount);
        void gainMana(int amount);
        void setState(State newState);
        State getState();
        int getSide();
        std::vector<Minion> &getGrave();
};

#endif
