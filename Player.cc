#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "Deck.h"

using namespace std;

Player::Player(string name) : name{name} {
    // DOUBLE CHECK AMOUNT OF CARDS IN DECK VS HAND *** currently 5 in hand, 15 deck
    //Create initial Deck - note this is all cards and not players deck
    Deck allCards = Deck(true);
    // Randomly choose 20 cards from all cards vector to go in deck
    // cards already shuffled in Deck constructor
    // put cards in deck
    for (int i = 0; i < 20; i++) {
        // point to instances of classes that inherit from Card but are not abstract
        Card *cardToMove = allCards.cards.back();
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
    
    Card *drawnCard = deck.cards.back();
    // remove card from deck
    deck.cards.pop_back();
    // put card in hand
    hand.push_back(drawnCard);
}
