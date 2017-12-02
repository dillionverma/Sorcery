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
  if (playerNum == 1) {
      return cardsP1;
  } else {
      return cardsP2;
  }
}


void Board::toGrave(int slot, int playerNum) {
    Player *player = (playerNum == 1) ? playerOne : playerTwo;
    Player *opponent = (player == playerOne) ? playerTwo : playerOne;
    vector<shared_ptr<Minion>> &cards = (playerNum == 1) ? getCards(1) : getCards(2);
    player->getGrave().push_back(cards[slot-1]);
    cards.erase(cards.begin() + slot - 1);
    player->setState(State::MinionLeave);
    player->notifyObservers();
    opponent->setState(State::MinionLeaveOpp);
    opponent->notifyObservers();
}

void Board::toHand(int slot, int playerNum) {
    Player *player = (playerNum == 1) ? playerOne : playerTwo;
    Player *opponent = (player == playerOne) ? playerTwo : playerOne;
    vector<shared_ptr<Minion>> cards = (playerNum == 1) ? getCards(1) : getCards(2);
    player->getHand().push_back(cards[slot-1]);
    cards.erase(cards.begin() + slot - 1);
    player->setState(State::MinionLeave);
    player->notifyObservers();
    opponent->setState(State::MinionLeaveOpp);
    opponent->notifyObservers();
}

void Board::playCardP1(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerOne->getHand().at(slot - 1);              // slot - 1 becauase vector starts 0, slot starts 1
  playerOne->getHand().erase(playerOne->getHand().begin() + slot - 1); // must erase 

  if (otherSlot == 0 && player == 0) {          // if we are playing a card which does not target other things
    if (c->getType() == "Minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP1.push_back(dynamic_pointer_cast<Minion>(c));
      playerOne->setState(State::MinionEnter);
      playerOne->notifyObservers();
      playerTwo->setState(State::MinionEnterOpp);
      playerTwo->notifyObservers();
      cout << "Minion added to P1 field: " << cardsP1.back()->getName() << endl;
    } else if (c->getType() == "Spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "Ritual") {
        ritualP1 = dynamic_pointer_cast<Ritual>(c);
    }

  } else {
    // implement cards which target other things

  }

}

void Board::playCardP2(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerTwo->getHand().at(slot - 1); // slot - 1 becauase vector starts 0, slot starts 1
  playerTwo->getHand().erase(playerTwo->getHand().begin() + slot - 1); // must erase because we used "move" previous line


  if (otherSlot == 0) {          // if we are playing a card which does not target other things
    if (c->getType() == "Minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP2.push_back(dynamic_pointer_cast<Minion>(c));
      playerTwo->setState(State::MinionEnter);
      playerTwo->notifyObservers();
      playerOne->setState(State::MinionEnterOpp);
      playerOne->notifyObservers();
      cout << "Minion added to P2 field: " << cardsP2.back()->getName() << endl;
    } else if (c->getType() == "Spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "Ritual") {
        ritualP2 = dynamic_pointer_cast<Ritual>(c);
    }
  } else {
    // implement cards which target other things
    

  }
}

void Board::attackMinion(int currentPlayer, int minion, int otherMinion) {
  int otherPlayer = (currentPlayer == 1) ? 2 : 1;
  shared_ptr<Minion> m1 = getCards(currentPlayer).at(minion - 1);
  shared_ptr<Minion> m2 = getCards(otherPlayer).at(otherMinion - 1);
  m1->attackMinion(*m2);
  if (m1->getDefence() <= 0) toGrave(minion, currentPlayer);
  if (m2->getDefence() <= 0) toGrave(otherMinion, otherPlayer);
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
  shared_ptr<Ritual> ritual = (playerNum == 1 ? ritualP1 : ritualP2); 

  vector<shared_ptr<Minion>> cards = getCards(playerNum);
  for(unsigned int i = 0; i < cards.size(); ++i) {
      cards[i]->notify(*this, p);
  }
  if (ritual) ritual->notify(*this, p);
}

shared_ptr<Ritual> Board::getRitual(int playerNum) const {
    if (playerNum == 1) {
        return ritualP1;
    } else {
        return ritualP2;
    }

}

void Board::setRitual(shared_ptr<Ritual> ritual, int playerNum) {
    if (playerNum == 1) {
        ritualP1 = ritual;    
    } else {
        ritualP2 = ritual;
    }
}

void Board::display() {
  const int p1mc = cardsP1.size(); 
  const int p2mc = cardsP2.size(); 
  bool p1Grave = (playerOne->getGrave().size() != 0);
  bool p2Grave = (playerTwo->getGrave().size() != 0);

  // Print top border of board
  cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < boardWidth; ++i) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;

  // Print first row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    if (ritualP1) {
      cout << ritualP1->display()[i];
    } else {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << CARD_TEMPLATE_EMPTY[i];
    cout << playerOne->display()[i];
    cout << CARD_TEMPLATE_EMPTY[i];
    if (p1Grave) {
      cout << playerOne->getGrave().back()->display()[i];
    } else {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print second row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < p1mc; ++j) {
      cout << cardsP1.at(j)->display()[i];
    }
    for (int j = p1mc; j < 5; ++j) {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print Sorcery
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) cout << CENTRE_GRAPHIC[i] << endl;

  // Print third row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (int j = 0; j < p2mc; ++j) {
      cout << cardsP2.at(j)->display()[i];
    }
    for (int j = p2mc; j < 5; ++j) {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print fourth row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    if (ritualP2) {
      cout << ritualP2->display()[i];
    } else {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << CARD_TEMPLATE_EMPTY[i];
    cout << playerTwo->display()[i];
    cout << CARD_TEMPLATE_EMPTY[i];
    if (p2Grave) {
      cout << playerTwo->getGrave().back()->display()[i];
    } else {
      cout << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print bottom border of board
  cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < boardWidth; ++i) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}
