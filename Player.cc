#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Player.h"
#include "Spell.h"
#include "Enchantment.h"

using namespace std;

Player::Player(string name, int playerNum, string deckfile) : name {name}, 
  playerNum {playerNum}, state{State::NoState}, deck{deckfile} {}    
   
void Player::drawFromDeck(int num) {
    // check first that hand is not full
    if (hand.size() == 5) {
        cout << "No cards drawn from deck as hand is full." << endl;
        return;
    } 

    // ensure there are cards in deck
    if (deck.cards.size() == 0) {
        cout << "No cards drawn from deck as deck is empty." << endl;
        return;
    }

    for (int i = 0; i < num; ++i) {
      shared_ptr<Card> drawnCard = deck.cards.front();
      deck.cards.erase(deck.cards.begin());     // remove card from deck
      hand.push_back(drawnCard);                // put card in hand 
    }
    notifyObservers();

    if (num == 1) {
        cout << "Card is drawn from deck." << endl;
    } else {
        // used at beginning 
        cout << num << " cards drawn from deck for " << name << "." << endl;
    }
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
string Player::getName() const { return name; }
bool Player::getActive() const { return active; }

// Mutable Getters
vector<shared_ptr<Minion>> &Player::getGrave() { return grave; }
vector<shared_ptr<Card>>   &Player::getHand()  { return hand; }

// Changers
void Player::changeHealth(const int amount) { health += amount; notifyObservers(); }
void Player::changeMana(const int amount)   { mana += amount; }

// Setters
void Player::setState(const State newState) { state = newState; }
void Player::setActive(const bool a) { active = a; }


void Player::removeFromHand(int slot) { hand.erase(hand.begin() + slot - 1); notifyObservers(); }
void Player::shuffleDeck() { deck.shuffle(); }
card_template_t Player::display() { return display_player_card(playerNum, name, health, mana); }


void Player::notifyObservers() {
    for(unsigned int i = 0; i < observers.size(); ++i) {
        observers[i]->notify(*this);
    }
}

void Player::setMana(const int amount) {
    mana = amount;
}

