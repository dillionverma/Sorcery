#include <string>
#include <iostream>
#include "Minion.h"
#include "Player.h"

using namespace std;

Minion::Minion(string name, int cost, string info, int attack, int defence, int abilityCost):
    Card{name, cost, info, "minion"}, attack{attack}, defence{defence}, abilityCost(abilityCost)  {} 

void Minion::changeAttack(int amount) { attack += amount; }
void Minion::changeDefence(int amount) { defence += amount; }

int Minion::getAttack() const { return attack;}
int Minion::getDefence() const { return defence;}

void Minion::display() {
    // note: the manifest must be altered to support printing minions with abilities
    card_template_t card = display_minion_no_ability(name, cost, attack, defence);
    printCard(card);
}

void Minion::attackMinion(Minion &m) {
  defence -= m.attack;
  m.defence -= m.attack;
}

void Minion::attackPlayer(Player &p) {
  p.changeHealth( -1 * attack);
}

void Minion::notify(Board &b, Player &p) {
}

