#ifndef OBSERVER_H
#define OBSERVER_H

class Player;
class Board;

class Observer {
    public:
        virtual void notify(Player &p)=0;
};

#endif
