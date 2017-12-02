#include <vector>
#include "Enrage.h"
#include "Board.h"
#include "Player.h"

using namespace std;

Enrage::Enrage(Component *component): Decorator(component) {
    comp = component;    
}

void Enrage::effect(Board &b, Player &p, int target) {

    comp->effect(b, p, target);

    // double minion attack and defence
    int playerNum = p.getNum();
    vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
    if ((int)minions.size() >= target) {
        shared_ptr<Minion> targetMin = minions.at(target - 1);
        int minionDefence = targetMin->getDefence();
        int minionAttack = targetMin->getAttack();
        targetMin->changeDefence(minionDefence);
        targetMin->changeAttack(minionAttack);
    } else {
        cout << "Invalid target minion. No minion exists in that position." << endl;
    }
}
