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

void Decorator::changeAction(const int amount) {
    minion->changeAction(amount);
}

void Decorator::setAction(const int amount) {
    minion->setAction(amount);
}

string Decorator::getName() const {
    return minion->getName();
}

string Decorator::getInfo() const {
    return minion->getInfo();
}

int Decorator::getCost() const {
    return minion->getCost();
}

int Decorator::getAction() const {
    return minion->getAction();
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

string Decorator::getAA() const { return minion->getAA(); }
string Decorator::getTA() const { return minion->getTA(); }
int Decorator::getAADamage() const { return minion->getAADamage(); }
string Decorator::getSummonName() const { return minion->getSummonName(); }
int Decorator::getSummonAmount() const { return minion->getSummonAmount(); }

void Decorator::attackMinion(Minion &m) {
  minion->changeDefence(-m.getAttack());
  m.changeDefence(-minion->getAttack());
}

void Decorator::attackPlayer(Player &p) {
  p.changeHealth( -1 * minion->getAttack());
}

card_template_t Decorator::display() {
    if (!minion->getTA().empty()) {
      return display_minion_triggered_ability(minion->getName(), minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getInfo());
    } else if(!minion->getAA().empty()) {
      return display_minion_activated_ability(minion->getName(), minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getAC(), minion->getInfo());
    } else {
      return display_minion_no_ability(minion->getName(), minion->getCost(), minion->getAttack(), minion->getDefence());
    }
}

void Decorator::notify(Board &b, Player &p, int target) {
    minion->notify(b, p, target);
}
