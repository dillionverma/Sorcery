#include <string>
#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(string name, int cost, string info):
    Card{name, cost, info, "Enchantment"} {};

void Enchantment::display() {
     //will implement later
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
    int playerNum = p.getNum();

    // double minion attack and defence
   if (name == "Enrage") {
        vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
        
        if ((int)minions.size() >= target) {
            shared_ptr<Minion> targetMin = minions.at(target - 1);
            int minionDefence = targetMin->getDefence();
            int minionAttack = targetMin->getAttack();
            targetMin->changeDefence(minionDefence);
            targetMin->changeAttack(minionAttack);
        
            targetMin->addEnchantment("Enrage");
        } else {
            cout << "Invalid target minion. No minion exists in that position." << endl;
        }
   } 
   // plus two minion attack and defence
   else if (name == "Giant Strength") {
        vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
        
        if ((int)minions.size() >= target) {
            shared_ptr<Minion> targetMin = minions.at(target - 1);
            targetMin->changeDefence(2);
            targetMin->changeAttack(2);
         
            targetMin->addEnchantment("Giant Strength");
        } else {
            cout << "Invalid target minion. No minion exists in that position." << endl;
        }
   } 
   // Enchanted minion gains +1 action each turn
   else if (name == "Haste") {
        // Advanced enchantment: Part P
   } 
   // Enchanted minion's activated ability costs 2 more
   else if (name == "Magic Fatigue") {                
        vector<shared_ptr<Minion>> minions = b.getCards(playerNum);

        if ((int)minions.size() >= target) {
            shared_ptr<Minion> targetMin = minions.at(target - 1);
            targetMin->changeAC(2);

            targetMin->addEnchantment("Magic Fatigue");
        } else {
            cout << "Invalid target minion. No minion exists in that position." << endl;
        }
   } 
   // Enchanted minion cannot use abilites
   else if (name == "Silence") {
        // Advanced enchantment: Part P
   }
}
