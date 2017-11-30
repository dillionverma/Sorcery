#include "Board.h"

using namespace std;

Board::Board() {}

void Board::setP1(Player *p) {
    playerOne = p;
}

void Board::setP2(Player *p) {
    playerTwo = p;
}

vector<Minion> &Board::getCardsP1() {
    return cardsP1;
}

vector<Minion> &Board::getCardsP2() {
    return cardsP2;
}

void Board::toGraveP1(int slot) {
    playerOne->getGrave().push_back(cardsP1[slot]);
    cardsP1.erase(cardsP1.begin() + slot);
}

void Board::toGraveP2(int slot) {
    playerTwo->getGrave().push_back(cardsP2[slot]);
    cardsP2.erase(cardsP2.begin() + slot);
}

Ritual &Board::getRitual(Player player) {
    if (player.getNum() == 1) {
        return *ritualP1;
    } else {
        return *ritualP2;
    }
}
