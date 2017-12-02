#include <vector>
#include "GiantStrength.h"
#include "Board.h"
#include "Player.h"

using namespace std;

GiantStrength::GiantStrength(Component *component): Decorator(component) {
    comp = component;    
}

void GiantStrength::effect(Board &b, Player &p, int target) {

    comp->effect(b, p, target);

    // double minion attack and defence
    int playerNum = p.getNum();
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
