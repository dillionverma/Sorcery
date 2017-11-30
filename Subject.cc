#include "Subject.h"

using namespace std;

void Subject::addObserver(Observer *o) {
    observers.push_back(o);
}

void Subject::setState(State newState) {
    state = newState;
}

State Subject::getState() const {
    return state;
}

