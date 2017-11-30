#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "Player.h"
#include "Ritual.h"
#include "Minion.h"
#include "Observer.h"

class Subject;

class Board: public Observer {
    Player *playerOne = nullptr;
    Player *playerTwo = nullptr;;
    Ritual *ritualP1 = nullptr;
    Ritual *ritualP2 = nullptr;
    std::vector<Minion> cardsP1;
    std::vector<Minion> cardsP2;
    public:
        Board();
        void setP1(Player *p);
        void setP2(Player *p);
        std::vector<Minion> &getCardsP1();
        std::vector<Minion> &getCardsP2();
        void toGraveP1(int slot);
        void toGraveP2(int slot);
        void notify(Player &p) override;
};

#endif
