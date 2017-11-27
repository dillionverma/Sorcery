#include <string>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info):
    Card{name, cost, info} {}

void Spell::playCard() {

}
