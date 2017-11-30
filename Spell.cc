#include <string>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info):
    Card{name, cost, info, "spell"} {}

void Spell::display() {
    card_template_t card = display_spell(name, cost, info);
    printCard(card);
}

void Spell::notify(Board &b, Player &p) {
}
