#include <vector>
#include "Silence.h"
#include "Board.h"
#include "Player.h"

using namespace std;

Silence::Silence(Component *component): Decorator(component) {
    comp = component;    
}

void Silence::effect(Board &b, Player &p, int target) {

    // comp->effect(b, p, target);
    // Enchanted minion cannot use abilites
    // Part p
}
