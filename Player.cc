#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "Deck.h"

using namespace std;

Player::Player(string name) : name{name} {
    // DOUBLE CHECK AMOUNT OF CARDS IN DECK VS HAND
    
    //Create initial Deck - note this is all cards and not players deck
    Deck allCards = Deck();

    // Randomly choose 20 cards from all cards vector to go in deck
    // cards already shuffled in Deck constructor
    // put cards in deck
    for (int i = 0; i < 20; i++) {
        // point to instances of classes that inherit from Card but are not abstract
        Card *cardToMove = allCards.cards.back();
        allCards.cards.pop_back();

        if (i < 15) {
            deck.cards.push_back(cardToMove);
            cardToMove->changeLocation(Card::Location::Deck);
        } else {
        // put last five cards in hand (all random)
            hand.push_back(cardToMove);
            cardToMove->changeLocation(Card::Location::Hand);
        }
    }
}    
   

void Player::drawFromDeck() {
    // check first that hand is not full
    if (hand.size() == 5) {
        // print out msg?
        return;
    } 
    
    Card *drawnCard = deck.cards.back();
    // remove card from deck
    deck.cards.pop_back();
    // put card in hand
    hand.push_back(drawnCard);

    drawnCard->changeLocation(Card::Location::Hand);
}
