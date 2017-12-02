#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>
#include "Deck.h"
#include "BasicMinion.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"

using namespace std;

Deck::Deck(string deckfile) {
  ifstream deck(deckfile); // open *.deck file
  string cardName;
  while (getline(deck, cardName)) { // iterate through each card name
    cardName.erase(std::remove(cardName.begin(),cardName.end(),' '),cardName.end()); // remove whitespace
    ifstream card("cards/" + cardName + ".txt"); // open card info file
    string line;
    getline(card, line);

    istringstream cardVals(line); // work with card values
    string name, type, description, tempCost;
    int cost;
    getline(cardVals, name, '|');
    getline(cardVals, type, '|');
    getline(cardVals, description, '|');
    getline(cardVals, tempCost, '|');
    cost = stoi(tempCost);

    // constructors for various card types
    if (type == "Minion") {
        // Minion has more info to take in
        string tempAtk, tempDef, tempAC, triggeredAbility;
        int attack, defence, abilityCost;

        getline(cardVals, triggeredAbility, '|');
        getline(cardVals, tempAtk, '|');
        getline(cardVals, tempDef, '|');
        getline(cardVals, tempAC, '|');
        attack = stoi(tempAtk);
        defence = stoi(tempDef);
        abilityCost = stoi(tempAC);

        shared_ptr<Card> newMinion = make_shared<BasicMinion>(name, cost, description,
                attack, defence, triggeredAbility, abilityCost);
        cards.push_back(newMinion);
    }

    if (type == "Enchantment") {
        shared_ptr<Card> newEnchantment = make_shared<Enchantment>(name, cost, description);
        cards.push_back(newEnchantment);
    }

    if (type == "Spell") {
        shared_ptr<Card> newSpell = make_shared<Spell>(name, cost, description);
        cards.push_back(newSpell);
    }

    if (type == "Ritual") {
        //Rituals have more info to take in
        string tempNC, tempAC;
        int numCharges, activationCost;

        getline(cardVals, tempNC, '|');
        getline(cardVals, tempAC, '|');

        numCharges = stoi(tempNC);
        activationCost = stoi(tempAC);

        shared_ptr<Card> newRitual = make_shared<Ritual>(name, cost, description, numCharges, activationCost);
        cards.push_back(newRitual);
    } 
  }
  shuffle(); // shuffle deck
}

// function for randomness factor
int myrandom (int i) {  
  return std::rand()%i;
}

void Deck::shuffle() {
  random_shuffle(cards.begin(), cards.end(), myrandom);
}

