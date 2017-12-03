#include <string>
#include <vector>
#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(string name, int cost, string info, int attack, int defence): Card{name, cost, info, "Enchantment"}, attack {attack}, defence {defence} {};

card_template_t Enchantment::display() {
    if (attack != 0 && defence != 0) {
        string prefix = "";
        if (name == "Giant Strength") {prefix = "+";}
        if (name == "Enrage") {prefix = "*";}
        return display_enchantment_attack_defence(name, cost, info, prefix+to_string(attack), prefix+to_string(defence));
    } else {
    return display_enchantment(name, cost, info);
    }
}

void Enchantment::notify(Board &b, Player &p, int target) {
}
