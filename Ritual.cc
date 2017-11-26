#include <string>
#include "Ritual.h"

using namespace std;

Ritual::Ritual(string name, int cost, string info, Card::Location location, 
    int numCharges, int activationCost):
    Card{name, cost, info, location},
    numCharges{numCharges}, activationCost{activationCost} {}

void Ritual::playCard() {

}
