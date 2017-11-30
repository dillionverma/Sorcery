#include <iostream>
#include "Board.h"
#include "Card.h"

using namespace std;

Board::Board() {}

void Board::setP1(Player *p) {
    playerOne = p;
}

void Board::setP2(Player *p) {
    playerTwo = p;
}

vector<shared_ptr<Minion>> &Board::getCards(int playerNum) {
  if (playerNum == 1) return cardsP1;
  if (playerNum == 2) return cardsP2;
}


void Board::toGrave(int slot, int playerNum) {
  if (playerNum == 1) {
    playerOne->getGrave().push_back(cardsP1[slot]);
    cardsP1.erase(cardsP1.begin() + slot - 1);
  } else {
    playerTwo->getGrave().push_back(cardsP2[slot]);
    cardsP2.erase(cardsP2.begin() + slot - 1);
  }
}

void Board::playCardP1(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerOne->getHand().at(slot - 1);              // slot - 1 becauase vector starts 0, slot starts 1
  playerOne->getHand().erase(playerOne->getHand().begin() + slot - 1); // must erase 

  if (otherSlot == 0 && player == 0) {          // if we are playing a card which does not target other things
    if (c->getType() == "minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP1.push_back(dynamic_pointer_cast<Minion>(c));
      cout << "Minion added to P1 field: " << cardsP1.back()->getName() << endl;
    } else if (c->getType() == "spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "ritual") {
      cout << "Playing ritual: " << c->getName() << endl;
    }

  } else {
    // implement cards which target other things

  }

}

void Board::playCardP2(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerTwo->getHand().at(slot - 1); // slot - 1 becauase vector starts 0, slot starts 1
  playerTwo->getHand().erase(playerTwo->getHand().begin() + slot - 1); // must erase because we used "move" previous line


  if (otherSlot == 0) {          // if we are playing a card which does not target other things
    if (c->getType() == "minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP2.push_back(dynamic_pointer_cast<Minion>(c));
      cout << "Minion added to P2 field: " << cardsP2.back()->getName() << endl;
    } else if (c->getType() == "spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "ritual") {
      cout << "Playing ritual: " << c->getName() << endl;
    }
  } else {
    // implement cards which target other things
    

  }
}


void Board::attackMinion(int currentPlayer, int minion, int otherMinion) {
  int otherPlayer = (currentPlayer == 1 ? 2 : 1);
  getCards(currentPlayer).at(minion - 1)->attackMinion(*getCards(otherPlayer).at(otherMinion - 1));
}

void Board::attackPlayer(int currentPlayer, int minion) {
  Player *otherPlayer = (currentPlayer == 1 ? playerTwo : playerOne);
  getCards(currentPlayer).at(minion - 1)->attackPlayer(*otherPlayer);
}

void Board::inspect(int currentPlayer, int slot) {
  shared_ptr<Card> c = getCards(currentPlayer).at(slot - 1);
  cout << "This card is a: " << c->getType() << endl;
  cout << "Minion Name: " << c->getName() << endl;
  cout << "Minion Info: " << c->getInfo() << endl;
}

void Board::notify(Player &p) {
  int playerNum = p.getNum();
  Ritual *ritual = (playerNum == 1 ? ritualP1 : ritualP2); 

  vector<shared_ptr<Minion>> cards = getCards(playerNum);
  for(unsigned int i = 0; i < cards.size(); ++i) {
      cards[i]->notify(*this, p);
  }
  ritual->notify(*this, p);
}
