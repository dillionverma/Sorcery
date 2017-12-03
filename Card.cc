#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "Card.h"
#include "BasicMinion.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"

using namespace std;

Card::Card(string name, int cost, string info, string type):
     name{name}, cost{cost}, info{info}, type{type} {}
    
Card::Card() {}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

string Card::getInfo() const {
    return info;
}

string Card::getType() const {
  return type;
}


shared_ptr<Card> Card::load(string cardName) {

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
