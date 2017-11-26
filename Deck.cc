#include <vector>
#include <string>
#include <fstream>
#include "Deck.h"
#include "Minion.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"

using namespace std;

Deck::Deck() {
    // Create vector containing ALL possible cards
    vector<Card *> allCards;
    
    // reading from formatted file
    ifstream f("CardList.txt");
    string line;

    while(getline(f, line)) {
        // check if its a commented line
        if (line.at(0) == '/') {
            continue;
        }
        
        string name;
        getline(f, name, '|');

        string type;
        getline(f, type, '|');

        string description;
        getline(f, description, '|');
    
        string tempCost;
        int cost;
        getline(f, tempCost, '|');
        cost = stoi(tempCost);

        // constructors for various card types
        if (type == "Minion") {
            // Minion has more info to take in
            string tempAtk, tempDef, tempAC;
            int attack, defense, abilityCost;

            getline(f, tempAtk, '|');
            attack = stoi(tempAtk);

            getline(f, tempDef, '|');
            defense = stoi(tempDef);

            getline(f, tempAC, '|');
            abilityCost = stoi(tempAC);

            Minion newMinion = Minion(name, cost, description, Card::Location::None,
                attack, defense, abilityCost);
            allCards.push_back(&newMinion);

        }

        if (type == "Enchantment") {
            Enchantment newEnchantment = Enchantment(name, cost, description,
                Card::Location::None);
            allCards.push_back(&newEnchantment);
        }

        if (type == "Spell") {
            Spell newSpell = Spell(name, cost, description, Card::Location::None);
            allCards.push_back(&newSpell);
        }

        if (type == "Ritual") {
            //Riruals have more info to take in
            string tempNC, tempAC;
            int numCharges, activationCost;

            getline(f, tempNC, '|');
            numCharges = stoi(tempNC);

            getline(f, tempAC, '|');
            activationCost = stoi(tempAC);
       
            Ritual newRitual = Ritual(name, cost, description, Card::Location::None,
                numCharges, activationCost);
            allCards.push_back(&newRitual);
        }
    }
}

void Deck::shuffle() {
    //random_shuffle(cards.begin(), cards.end());
}
