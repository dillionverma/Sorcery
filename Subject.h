#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "State.h"

class Observer;
class Subject {
    protected:
        std::vector<Observer *> observers;
        State state;
    public:
        void addObserver(Observer *o);
        virtual void notifyObservers()=0;
        void setState(State newState);
        State getState() const;
};

#endif
