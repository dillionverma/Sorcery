#include "Haste.h"

using namespace std;

Haste::Haste(shared_ptr<Minion> minion): Decorator {minion} {
}

int Haste::getAction() const {
    return minion->getAction()+1;
}
