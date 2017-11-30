#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Player.h"
#include "Spell.h"
#include "Enchantment.h"

using namespace std;

Player::Player(string name, int playerNum) : name {name}, playerNum {playerNum} {
    state = State::None;
    // DOUBLE CHECK AMOUNT OF CARDS IN DECK VS HAND *** currently 5 in hand, 15 deck
    //Create initial Deck - note this is all cards and not players deck
    Deck allCards = Deck(true);
    // Randomly choose 20 cards from all cards vector to go in deck
    // cards already shuffled in Deck constructor
    // put cards in deck
    for (int i = 0; i < 20; ++i) {
        // point to instances of classes that inherit from Card but are not abstract
        shared_ptr<Card> cardToMove = allCards.cards.back();
        allCards.cards.pop_back();
        if (i < 15) {
            deck.cards.push_back(cardToMove);
       } else {
        // put last five cards in hand (all random)
            hand.push_back(cardToMove);
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
    for (auto card : hand) {
        card->display();
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

void Player::display() {
    card_template_t card = display_player_card(playerNum, name, health, mana);
    printCard(card);
}

