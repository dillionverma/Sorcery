#include "GiantStrength.h"

using namespace std;

GiantStrength::GiantStrength(shared_ptr<Minion> minion): Decorator {minion} {
}

int GiantStrength::getAttack() const {
    return minion->getAttack()+2;
}

int GiantStrength::getDefence() const {
    return minion->getDefence()+2;
}

void GiantStrength::attackMinion(Minion &m) {
  minion->changeDefence(-m.getAttack());
  m.changeDefence(-1 * (minion->getAttack()+2));
}

void GiantStrength::attackPlayer(Player &p) {
  p.changeHealth(-1 * (minion->getAttack()+2));
}

card_template_t GiantStrength::display() {
    //if (triggered_ability) {
      //return display_minion_triggered_ability(name, cost, attack, defence, trigger_desc);
    //} else if(activated_ability) {
      //return display_minion_activated_ability(name, cost, attack, defence, abilityCost, ability_desc);
    //} else {
      return display_minion_no_ability(minion->getName(), minion->getCost(), minion->getAttack()+2, minion->getDefence()+2);
    //}
}
