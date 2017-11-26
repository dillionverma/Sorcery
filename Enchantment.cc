#include <string>
#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(string name, int cost, string info, Card::Location location):
    Card{name, cost, info, location} {};

void Enchantment::playCard() {

}
