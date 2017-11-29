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

void Board::notify(Player &p) {
    vector<Minion> &cards = getCardsP1();
    Ritual *ritual = ritualP1;
    if (p.getNum() == 2) {
        cards = getCardsP2();
        ritual = ritualP2;
    }
    for(unsigned int i = 0; i < cards.size(); ++i) {
        cards[i].notify(*this, p);
    }
    ritual->notify(*this, p);
}

