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

