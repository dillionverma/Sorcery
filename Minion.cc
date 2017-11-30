#include <string>
#include "Minion.h"

using namespace std;

Minion::Minion(string name, int cost, string info, int attack, int defense, int abilityCost):
    Card{name, cost, info}, attack{attack}, defence{defence}, abilityCost(abilityCost)  {} 

void Minion::gainAtk(int amount) {
    attack += amount;
}

void Minion::gainDef(int amount) {
    defence += amount;
}

void Minion::display() {
    // will implement later
}

void Minion::notify(Board &b, Player &p) {
}
