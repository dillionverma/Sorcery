#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
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
    //vector<Card *> allCards;
    
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
            string tempAtk, tempDef, tempAC;
            int attack, defense, abilityCost;

            getline(cardVals, tempAtk, '|');
            attack = stoi(tempAtk);

            getline(cardVals, tempDef, '|');
            defense = stoi(tempDef);
 
            getline(cardVals, tempAC, '|');
            abilityCost = stoi(tempAC);

            Minion newMinion = Minion(name, cost, description,
                attack, defense, abilityCost);
            cards.push_back(&newMinion);
        }

        if (type == "Enchantment") {
            Enchantment newEnchantment = Enchantment(name, cost, description);
            cards.push_back(&newEnchantment);
        }

        if (type == "Spell") {
            Spell newSpell = Spell(name, cost, description);
            cards.push_back(&newSpell);
        }

        if (type == "Ritual") {
            //Riruals have more info to take in
            string tempNC, tempAC;
            int numCharges, activationCost;

            getline(cardVals, tempNC, '|');
            numCharges = stoi(tempNC);

            getline(cardVals, tempAC, '|');
            activationCost = stoi(tempAC);

            Ritual newRitual = Ritual(name, cost, description, 
                numCharges, activationCost);
            cards.push_back(&newRitual);
        } 
        }
    }
}

void Deck::shuffle() {
    random_shuffle(cards.begin(), cards.end());
}