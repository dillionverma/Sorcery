#include <string>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info):
    Card{name, cost, info, "spell"} {}

void Spell::display() {
     //will implement later
}
