#include <string>
#include "Ritual.h"

using namespace std;

Ritual::Ritual(string name, int cost, string info,
    int numCharges, int activationCost):
    Card{name, cost, info},
    numCharges{numCharges}, activationCost{activationCost} {}

void Ritual::playCard() {

}
