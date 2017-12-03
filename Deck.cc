#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <memory>
#include "Deck.h"
#include "Card.h"

using namespace std;

Deck::Deck(string deckfile) {
  ifstream deck(deckfile); // open *.deck file
  string cardName;
  while (getline(deck, cardName)) { // iterate through each card name
    shared_ptr<Card> c = Card::load(cardName);
    cards.push_back(c);
  }
}

// function for randomness factor
int myrandom (int i) {  
  return std::rand()%i;
}

void Deck::shuffle() {
  random_shuffle(cards.begin(), cards.end(), myrandom);
}

