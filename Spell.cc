#include <string>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info, Card::Location location):
    Card{name, cost, info, location} {}

void Spell::playCard() {

}
