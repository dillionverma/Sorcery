#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>
#include "Deck.h"
#include "Minion.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"

using namespace std;

Deck::Deck(bool isFullDeck) {
    // only needed when creating all cards, otherwise, cards are added
    //  to player's deck in Player class
    if (isFullDeck) {
        // Create vector containing ALL possible cards

        // reading from formatted file
        ifstream f("CardList.txt");
        string line = " ";

        while(getline(f, line)) {
            istringstream cardVals(line);
            // check if its a commented line
            if (line.at(0) == '/') {
                continue;
            } 

            string name;
            getline(cardVals, name, '|');

            string type;
            getline(cardVals, type, '|');

            string description;
            getline(cardVals, description, '|');

            string tempCost; 
            int cost;

            getline(cardVals, tempCost, '|');
            cost = stoi(tempCost);

            // constructors for various card types
            if (type == "Minion") {
                // Minion has more info to take in
                string tempAtk, tempDef, tempAC, triggeredAbility;
                int attack, defence, abilityCost;

                getline(cardVals, triggeredAbility, '|');

                getline(cardVals, tempAtk, '|');
                attack = stoi(tempAtk);

                getline(cardVals, tempDef, '|');
                defence = stoi(tempDef);

                getline(cardVals, tempAC, '|');
                abilityCost = stoi(tempAC);

                shared_ptr<Card> newMinion = make_shared<Minion>(name, cost, description,
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
                numCharges = stoi(tempNC);

                getline(cardVals, tempAC, '|');
                activationCost = stoi(tempAC);

                shared_ptr<Card> newRitual = make_shared<Ritual>(name, cost, description, 
                numCharges, activationCost);
                cards.push_back(newRitual);
            } 
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

