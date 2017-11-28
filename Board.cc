#include "Board.h"

using namespace std;

Board::Board() {}

void Board::setPlayerOne(Player *p) {
    playerOne = p;
}

void Board::setPlayerTwo(Player *p) {
    playerTwo = p;
}

vector<Minion> *Board::getCardsP1() {
    return &cardsP1;
}

vector<Minion> *Board::getCardsP2() {
    return &cardsP2;
}

void Board::toGraveP1(int slot) {
    playerOne->getGrave().push_back(cardsP1[slot]);
    cardsP1.erase(cardsP1.begin() + slot);
}

void Board::toGraveP2(int slot) {
    playerTwo->getGrave().push_back(cardsP2[slot]);
    cardsP2.erase(cardsP2.begin() + slot);
}

