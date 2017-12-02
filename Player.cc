#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Player.h"
#include "Spell.h"
#include "Enchantment.h"

using namespace std;

Player::Player(string name, int playerNum, string deckfile) : name {name}, playerNum {playerNum}, state{State::None}, deck{deckfile} {
  for (int i = 0; i < 5; ++i) {
    if (deck.cards.back()) { // check if exist
      shared_ptr<Card> c = deck.cards.back();
      hand.push_back(c);
      deck.cards.pop_back();
    }
  }
}    
   
void Player::drawFromDeck() {
    // check first that hand is not full
    if (hand.size() == 5) {
        cout << "No cards drawn from deck as hand is full." << endl;
        return;
    } 
    cout << "Card is drawn from deck." << endl;
    
    shared_ptr<Card> drawnCard = deck.cards.back();
    deck.cards.pop_back();     // remove card from deck
    hand.push_back(drawnCard); // put card in hand
}

void Player::showHand() { 
  for (int i = 0; i < cardHeight; ++i) {
    for (auto c:hand) {
      if (c->getType() == "Minion") cout << green << c->display()[i];
      if (c->getType() == "Enchantment") cout << cyan << c->display()[i];
      if (c->getType() == "Ritual") cout << magenta << c->display()[i];
      if (c->getType() == "Spell") cout << blue << c->display()[i];
    }
    cout << reset << endl;
  }
}

// Constant Getters
State Player::getState() const { return state; }
int Player::getNum()     const { return playerNum; }
int Player::getHealth()  const { return health; }
int Player::getMana()    const { return mana; }

// Mutable Getters
vector<shared_ptr<Minion>> &Player::getGrave() { return grave; }
vector<shared_ptr<Card>>   &Player::getHand()  { return hand; }

// Changers
void Player::changeHealth(const int amount) { health += amount; }
void Player::changeMana(const int amount)   { mana += amount; }

// Setters
void Player::setState(const State newState) { state = newState; }

void Player::notifyObservers() {
    for(unsigned int i = 0; i < observers.size(); ++i) {
        observers[i]->notify(*this);
    }
}


void Player::removeFromHand(int slot) {
  hand.erase(hand.begin() + slot - 1);
}


card_template_t Player::display() {
    card_template_t card = display_player_card(playerNum, name, health, mana);
    return card;
}

