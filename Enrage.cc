#include "Enrage.h"

using namespace std;

Enrage::Enrage(shared_ptr<Minion> minion): Decorator {minion} {
}

int Enrage::getAttack() const {
    return minion->getAttack()*2;
}

int Enrage::getDefence() const {
    return minion->getDefence()*2;
}

void Enrage::attackMinion(Minion &m) {
  minion->changeDefence(-m.getAttack());
  m.changeDefence(-1 * (minion->getAttack()*2));
}

void Enrage::attackPlayer(Player &p) {
  p.changeHealth(-1 * (minion->getAttack()*2));
}

card_template_t Enrage::display() {
    //if (triggered_ability) {
      //return display_minion_triggered_ability(name, cost, attack, defence, trigger_desc);
    //} else if(activated_ability) {
      //return display_minion_activated_ability(name, cost, attack, defence, abilityCost, ability_desc);
    //} else {
      return display_minion_no_ability(minion->getName(), minion->getCost(), minion->getAttack()*2, minion->getDefence()*2);
    //}
}
