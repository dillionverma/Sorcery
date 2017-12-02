#include <string>
#include <vector>
#include "Minion.h"
#include "Enchantment.h"
#include "Component.h"
#include "GiantStrength.h"
#include "Enrage.h"
#include "Haste.h"
#include "MagicFatigue.h"
#include "Silence.h"

using namespace std;

Enchantment::Enchantment(string name, int cost, string info): 
    Card{name, cost, info, "Enchantment"}  {};

card_template_t Enchantment::display() {
  //if (attack_defence_enchantment) {
    //return display_enchantment_attack_defence(name, cost, info, attack, defence);
  //} else {
    return display_enchantment(name, cost, info);
  //}
}

void Enchantment::notify(Board &b, Player &p, int target) {
    // ensure player can afford to play card
    if (p.getMana() >= cost) {
        effect(b, p, target);
        p.changeMana(-cost);
    } else {
        cout << "You do not have enough magic to play this card." << endl;
    }
}

void Enchantment::effect(Board &b, Player &p, int target) {
    // a basic enchantment will theoretically not exist
    // not 100% sure about this


vector<shared_ptr<Minion>> minions = b.getCards(p.getNum());
shared_ptr<Minion> targetMin = minions.at(target - 1);
int numEnchants = targetMin->getNumEnchants();
for (int i = 0; i < numEnchants; i++) { 
//    Component *comp = new Enchantment("Test", 1, "Test2");
    if (name == "Giant Strength") {
     //   comp = new GiantStrength(comp);
    } else if (name == "Enrage") {
     //   comp = new Enrage(comp);
    } else if (name == "Haste") {
     //   comp = new Haste(comp);
    } else if (name == "MagicFatigue") {
     //   comp = new MagicFatigue(comp);
    } else if (name == "Silence") {
      //  comp = new Silence(comp);
    }
  //  comp->effect(b, p, target);
}

}
