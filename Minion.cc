#include <string>
#include "Minion.h"

using namespace std;

Minion::Minion(string name, int cost, string info, int attack,
    int defense, int abilityCost):
    Card{name, cost, info}, attack{attack}, 
    defense{defense}, abilityCost(abilityCost)  {} 

void Minion::playCard() {
}
