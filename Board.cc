#include <iostream>
#include "Board.h"
#include "Card.h"
#include "GiantStrength.h"
#include "Enrage.h"
#include "Silence.h"

using namespace std;

Board::Board() {}

void Board::setPlayer(Player *p, int playerNum) {
  if (playerNum == 1) {
    playerOne = p;
  } else {
    playerTwo = p;
  }
}

void Board::endTurn(Player *activePlayer, Player *nonActivePlayer) {
  // end of turn events occur for current player
  activePlayer->setState(State::EndTurn);
  activePlayer->notifyObservers();
  nonActivePlayer->setState(State::EndTurnOpp);
  nonActivePlayer->notifyObservers();
  //swap(activePlayer, nonActivePlayer);
  // activePlayer.updateMana(activePlayer.mana++);
  nonActivePlayer->drawFromDeck(1);
  nonActivePlayer->setState(State::StartTurn);
  nonActivePlayer->notifyObservers();
  activePlayer->setState(State::StartTurnOpp);
  activePlayer->notifyObservers();
  // beginning of turn events occur for new player
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

  if (otherSlot == -1 && player == -1) {          // if we are playing a card which does not target other things
    if (c->getType() == "Minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP1.push_back(dynamic_pointer_cast<Minion>(c));
      playerOne->setState(State::MinionEnter);
      playerOne->notifyObservers();
      playerTwo->setState(State::MinionEnterOpp);
      playerTwo->notifyObservers();
    } else if (c->getType() == "Spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "Ritual") {
      ritualP1 = dynamic_pointer_cast<Ritual>(c);
    }

  } else {
      if (c->getType() == "Enchantment") {
          shared_ptr<Minion> target = cardsP1[otherSlot-1];
          if (c->getName() == "Giant Strength") {
              cardsP1[otherSlot-1] = make_shared<GiantStrength>(GiantStrength(target));
          } else if (c->getName() == "Enrage") {
              cardsP1[otherSlot-1] = make_shared<Enrage>(Enrage(target));
          } else if (c->getName() == "Silence") {
               cardsP1[otherSlot-1] = make_shared<Silence>(Silence(target));
          }
      }
  }

}
    

void useActivatedAbility(int currentPlayer, int slot, int player, int otherSlot) {

  if (otherSlot == -1 && player == -1) {

    // using activated ability with no target
  } else {
    // activated ability with target
  }
}

void Board::playCardP2(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerTwo->getHand().at(slot - 1); // slot - 1 becauase vector starts 0, slot starts 1
  playerTwo->getHand().erase(playerTwo->getHand().begin() + slot - 1); // must erase because we used "move" previous line


  if (otherSlot == -1 && player == -1) {          // if we are playing a card which does not target other things
    if (c->getType() == "Minion") {
      cout << "Playing minion: " << c->getName() << endl;
      cardsP2.push_back(dynamic_pointer_cast<Minion>(c));
      playerTwo->setState(State::MinionEnter);
      playerTwo->notifyObservers();
      playerOne->setState(State::MinionEnterOpp);
      playerOne->notifyObservers();
    } else if (c->getType() == "Spell") { // TODO: add && to check if spell requires no target
      cout << "Playing spell: " << c->getName() << endl;
    } else if (c->getType() == "Ritual") {
        ritualP2 = dynamic_pointer_cast<Ritual>(c);
    }
  } else {
      if (c->getType() == "Enchantment") {
          shared_ptr<Minion> target = cardsP2[otherSlot-1];
          if (c->getName() == "Giant Strength") {
              cardsP2[otherSlot-1] = make_shared<GiantStrength>(GiantStrength(target));
          } else if (c->getName() == "Enrage") {
              cardsP2[otherSlot-1] = make_shared<Enrage>(Enrage(target));
          } else if (c->getName() == "Silence") {
               cardsP2[otherSlot-1] = make_shared<Silence>(Silence(target));
          }

      }
  }
}

void Board::attackMinion(int currentPlayer, int minion, int otherMinion) {
  int otherPlayer = (currentPlayer == 1 ? 2 : 1);
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
  for (int i = 0; i < cardHeight; ++i) {
    cout << c->display()[i] << endl; // print card first
  }
  // PRINT ALL ENCHANTMENTS, 5 AT A TIME
  //int ctr = 1;
  //for (auto line:cardHeight) {
    //cout << c->displayEnchantmnets;
    //cout << c->displayEnchantmnets;
    //cout << c->displayEnchantmnets;
    //cout << c->displayEnchantmnets;
    //if (ctr%5 == 0) cout << endl;
    //ctr++;
  //}
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
  cout << yellow << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < boardWidth; ++i) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;

  // Print first row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << reset;
    if (ritualP1) {
      cout << cyan << ritualP1->display()[i] << reset;
    } else {
      cout << yellow << CARD_TEMPLATE_EMPTY[i];
    }
    cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    cout << white << playerOne->display()[i] << reset;
    cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    if (p1Grave) {
      cout << red << playerOne->getGrave().back()->display()[i] << reset;
    } else {
      cout << yellow << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print second row
  for (int i = 0; i < cardHeight; ++i) {
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << reset;
    for (int j = 0; j < p1mc; ++j) {
      cout << green << cardsP1.at(j)->display()[i] << reset;
    }
    for (int j = p1mc; j < 5; ++j) {
      cout << yellow << CARD_TEMPLATE_EMPTY[i];
    }
    cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
  }

  // Print Sorcery
  for (unsigned int i = 0; i < CENTRE_GRAPHIC.size(); ++i) cout << CENTRE_GRAPHIC[i] << endl;

  // Print third row
  for (int i = 0; i < cardHeight; ++i) {
    cout << yellow << EXTERNAL_BORDER_CHAR_UP_DOWN << reset;
    for (int j = 0; j < p2mc; ++j) {
      cout << green << cardsP2.at(j)->display()[i] << reset;
    }
    for (int j = p2mc; j < 5; ++j) {
      cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    }
    cout << yellow << EXTERNAL_BORDER_CHAR_UP_DOWN << reset << endl;
  }

  // Print fourth row
  for (int i = 0; i < cardHeight; ++i) {
    cout << yellow << EXTERNAL_BORDER_CHAR_UP_DOWN << reset;
    if (ritualP2) {
      cout << cyan << ritualP2->display()[i] << reset;
    } else {
      cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    }
    cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    cout << white << playerTwo->display()[i] << reset;
    cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    if (p2Grave) {
      cout << red << playerTwo->getGrave().back()->display()[i] << reset;
    } else {
      cout << yellow << CARD_TEMPLATE_EMPTY[i] << reset;
    }
    cout << yellow << EXTERNAL_BORDER_CHAR_UP_DOWN << reset << endl;
  }

  // Print bottom border of board
  cout << yellow << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < boardWidth; ++i) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << reset << endl;
}
