#include <string>
#include <iostream>
#include <vector>
#include "Minion.h"
#include "Player.h"

using namespace std;

Minion::Minion(string name, int cost, string info, int attack, int defence, int abilityCost):
    Card{name, cost, info, "Minion"}, attack{attack}, defence{defence}, abilityCost(abilityCost)  {} 

void Minion::changeAttack(int amount) { attack += amount; }
void Minion::changeDefence(int amount) { defence += amount; }
void Minion::changeAC(int amount) { abilityCost += amount; }

void Minion::addEnchantment(string newEnchant) {
    enchantments.push_back(newEnchant);
}

int Minion::getAttack() const { return attack;}
int Minion::getDefence() const { return defence;}
int Minion::getAC() const { return abilityCost; }
vector<string> Minion::getEnchants() const { return enchantments; }

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

void Minion::notify(Board &b, Player &p, int target) {
}

