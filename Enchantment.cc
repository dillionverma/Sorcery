#include <string>
#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(string name, int cost, string info):
    Card{name, cost, info, "enchantment"} {};

void Enchantment::display() {
     //will implement later
}
void Enchantment::notify(Board &b, Player &p) {
}
