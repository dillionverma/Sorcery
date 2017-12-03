#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Board.h"
#include "Minion.h"
#include "Subject.h"

class Player: public Subject {
  std::string name;
  int health = 20;
  int mana = 3;
  int playerNum;
  State state;
  Deck deck;
  std::vector<std::shared_ptr<Minion>> grave;
  std::vector<std::shared_ptr<Card>> hand;

  public:
    Player(std::string name, int side, std::string deckfile = "default.deck");
    void shuffleDeck();
    void drawFromDeck(int num);
    void changeHealth(const int amount);
    void changeMana(const int amount);
    void setState(const State newState);
    State getState() const;
    int getNum() const;
    int getHealth() const;
    void showHand();
    void notifyObservers() override;
    void removeFromHand(int slot); 
    int getMana() const;
    std::vector<std::shared_ptr<Minion>> &getGrave();
    std::vector<std::shared_ptr<Card>> &getHand();
    card_template_t display();
};

#endif
