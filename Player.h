#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "State.h"
#include "Minion.h"
#include "Ritual.h"

class Player {
    std::string name;
    int health = 20;
    int mana = 3;
    State state;
    Deck deck = Deck();
    Ritual *r = nullptr;
    Player *opponent = nullptr;
    std::vector<Card *> hand;
    std::vector<Card *> grave;
    std::vector<Minion *> field;

    public:
        Player(std::string name);
        void shuffleDeck(std::vector<Card *> deck);
        void drawFromDeck();
        void gainHealth(int amount);
        void gainMana(int amount);
        void setState(State newState);
        State getState();
        void minionGainAtk(int slot, int amount);
        void minionGainDef(int slot, int amount);
        int fieldSize();
        void setOpponent(Player *opp);
        Player *getOpponent();
        void toGrave(int slot);
};

#endif
