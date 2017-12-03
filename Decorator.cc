#include "Decorator.h"

using namespace std;

Decorator::Decorator(shared_ptr<Minion> minion): minion {minion} {}

void Decorator::changeAttack(const int amount) {
    minion->changeAttack(amount);
};

void Decorator::changeDefence(const int amount) {
    minion->changeDefence(amount);
}

void Decorator::changeAC(const int amount) {
    minion->changeAC(amount);
}

string Decorator::getName() const {
    return minion->getName();
}

int Decorator::getCost() const {
    return minion->getCost();
}

int Decorator::getAttack() const {
    return minion->getAttack();
}

int Decorator::getDefence() const {
    return minion->getDefence();
}

int Decorator::getAC() const {
    return minion->getAC();
}

void Decorator::attackMinion(Minion &m) {
  minion->changeDefence(-m.getAttack());
  m.changeDefence(-minion->getAttack());
}

void Decorator::attackPlayer(Player &p) {
  p.changeHealth( -1 * minion->getAttack());
}

card_template_t Decorator::display() {
    //if (triggered_ability) {
      //return display_minion_triggered_ability(name, cost, attack, defence, trigger_desc);
    //} else if(activated_ability) {
      //return display_minion_activated_ability(name, cost, attack, defence, abilityCost, ability_desc);
    //} else {
      return display_minion_no_ability(minion->getName(), minion->getCost(), minion->getAttack(), minion->getDefence());
    //}
}
