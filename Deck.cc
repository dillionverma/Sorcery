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
    shared_ptr<Card> c = loadCard(cardName);
    cards.push_back(c);
  }
}

shared_ptr<Card> Deck::loadCard(string cardName) {

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
      string tempAtk, tempDef, tempAC, tempAAdmg, tempSA, triggeredAbility, activatedAbility, summonMinion;
      int attack, defence, abilityCost, activatedAbilityDamage, summonAmount;

      getline(cardVals, triggeredAbility, '|');
      getline(cardVals, tempAtk, '|');
      getline(cardVals, tempDef, '|');
      getline(cardVals, tempAC, '|');
      getline(cardVals, activatedAbility, '|');
      if (activatedAbility == "Summon") {
        getline(cardVals, summonMinion, '|');
        getline(cardVals, tempSA, '|');
        summonAmount = stoi(tempSA);
        activatedAbilityDamage = 0;
      }
      if (activatedAbility == "Damage") {
        getline(cardVals, tempAAdmg, '|');
        activatedAbilityDamage = stoi(tempAAdmg);
        summonMinion = "";
        summonAmount = 0;
      }
      attack = stoi(tempAtk);
      defence = stoi(tempDef);
      abilityCost = stoi(tempAC);

      shared_ptr<Card> newMinion = make_shared<BasicMinion>(name, cost, description,
              attack, defence, triggeredAbility, activatedAbility, abilityCost,
              activatedAbilityDamage, summonMinion, summonAmount);
      return newMinion;
  }

  if (type == "Enchantment") {
      shared_ptr<Card> newEnchantment = make_shared<Enchantment>(name, cost, description);
      return newEnchantment;
  }

  if (type == "Spell") {
      shared_ptr<Card> newSpell = make_shared<Spell>(name, cost, description);
      return newSpell;
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
      return newRitual;
  } 
}

// function for randomness factor
int myrandom (int i) {  
  return std::rand()%i;
}

void Deck::shuffle() {
  random_shuffle(cards.begin(), cards.end(), myrandom);
}

