#include <vector>
#include "Haste.h"
#include "Board.h"
#include "Player.h"

using namespace std;

Haste::Haste(Component *component): Decorator(component) {
    comp = component;    
}

void Enrage::effect(Board &b, Player &p, int target) {
    // comp->effect(b, p, target);
    // Enchanted minion gains +1 action each turn
    // part p
}
