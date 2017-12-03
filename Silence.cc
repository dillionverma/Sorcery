#include "Silence.h"

using namespace std;

Silence::Silence(shared_ptr<Minion> minion): Decorator {minion} {
}

void Silence::notify(Board &b, Player &p, int target) {
}
