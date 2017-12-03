#include <string>
#include "Minion.h"

using namespace std;

Minion::Minion(string name, int cost, string info, int attack, int defence, string triggeredAbility, 
    string activatedAbility, int abilityCost):
    Card{name, cost, info, "Minion"}, attack{attack}, defence{defence}, 
    triggeredAbility {triggeredAbility}, abilityCost(abilityCost)  {}

Minion::Minion() {}
