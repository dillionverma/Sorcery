#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "Player.h"
#include "Ritual.h"
#include "Minion.h"

class Board {
    Player *playerOne = nullptr;
    Player *playerTwo = nullptr;;
    Ritual *ritualP1 = nullptr;
    Ritual *ritualP2 = nullptr;
    std::vector<Minion *>cardsP1;
    std::vector<Minion *>cardsP2;
    public:
        Board();
        void setPlayerOne(Player *p);
        void setPlayerTwo(Player *p);
        std::vector<Minion *> *getCardsP1();
        std::vector<Minion *> *getCardsP2();
        void toGraveP1(int slot);
        void toGraveP2(int slot);
};

#endif
