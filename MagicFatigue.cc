#include "MagicFatigue.h"

using namespace std;

MagicFatigue::MagicFatigue(shared_ptr<Minion> minion): Decorator {minion} {
}

int MagicFatigue::getAC() const {
    return minion->getAC() + 2;
};

