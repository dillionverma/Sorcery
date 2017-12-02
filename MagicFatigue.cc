#include <vector>
#include "MagicFatigue.h"
#include "Board.h"
#include "Player.h"

using namespace std;

MagicFatigue::MagicFatigue(Component *component): Decorator(component) {
    comp = component;    
}

void Enrage::effect(Board &b, Player &p, int target) {

    comp->effect(b, p, target);

    // Enchanted minion's activated ability costs 2 more
    int playerNum = p.getNum();
    vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
    if ((int)minions.size() >= target) {
        shared_ptr<Minion> targetMin = minions.at(target - 1);
        targetMin->changeAC(2);
        targetMin->addEnchantment("Magic Fatigue");
    } else {
        cout << "Invalid target minion. No minion exists in that position." << endl;
    }
}
