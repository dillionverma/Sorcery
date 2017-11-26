#include <string>
#include "Minion.h"

using namespace std;

Minion::Minion(string name, int cost, string info, Card::Location location, int attack,
    int defense, int abilityCost):
    Card{name, cost, info, location}, attack{attack}, 
    defense{defense}, abilityCost(abilityCost)  {} 

void Minion::playCard() {
}
