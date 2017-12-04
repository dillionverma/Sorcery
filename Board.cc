#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Card.h"
#include "GiantStrength.h"
#include "Enrage.h"
#include "Silence.h"
#include "MagicFatigue.h"
#include "Haste.h"

using namespace std;

Board::Board(bool testing): testing {testing} {}

void Board::setPlayer(Player *p, int playerNum) {
  if (playerNum == 1) {
    playerOne = p;
  } else {
    playerTwo = p;
  }
}

void Board::endTurn(Player *activePlayer, Player *nonActivePlayer) {
  activePlayer->setState(State::EndTurn);
  activePlayer->notifyObservers();
  nonActivePlayer->setState(State::EndTurnOpp);
  nonActivePlayer->notifyObservers();
  nonActivePlayer->changeMana(1);
  nonActivePlayer->drawFromDeck(1);
  nonActivePlayer->setState(State::StartTurn);
  nonActivePlayer->notifyObservers();
  activePlayer->setState(State::StartTurnOpp);
  activePlayer->notifyObservers();
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
    shared_ptr<Minion> m = cards[slot-1];
    cards.erase(cards.begin() + slot - 1);
    while (m->getEnchantments().size() > 0) {
        m->removeEnchantment();
        m = dynamic_pointer_cast<Decorator>(m)->getMinion();
    }
    player->getGrave().push_back(m);
    player->setState(State::MinionLeave);
    player->notifyObservers();
    opponent->setState(State::MinionLeaveOpp);
    opponent->notifyObservers();
    cout << "Minion sent to grave." << endl;
}

void Board::toHand(int slot, int playerNum) {
    Player *player = (playerNum == 1) ? playerOne : playerTwo;
    Player *opponent = (player == playerOne) ? playerTwo : playerOne;
    vector<shared_ptr<Minion>> &cards = (playerNum == 1) ? getCards(1) : getCards(2);
    shared_ptr<Minion> m = cards[slot-1];
    cards.erase(cards.begin() + slot - 1);
    while (m->getEnchantments().size() > 0) {
        m->removeEnchantment();
        m = dynamic_pointer_cast<Decorator>(m)->getMinion();
    }
    player->getHand().push_back(m);
    player->setState(State::MinionLeave);
    player->notifyObservers();
    opponent->setState(State::MinionLeaveOpp);
    opponent->notifyObservers();
}


void Board::useActivatedAbility(int playerNum, int slot, int targetPlayer, int otherSlot) {
  Player *player = (playerNum == 1) ? playerOne : playerTwo;
  vector<shared_ptr<Minion>> &cards = (playerNum == 1) ? cardsP1: cardsP2;
  shared_ptr<Minion> m = cards.at(slot - 1); 
  if (m->getAction() > 0 && ((player->getMana() - m->getAC() >= 0) || testing)) {
      if (otherSlot == -1 && targetPlayer == -1) {
        if (m->getAA() == "Summon") {
          int summonAmount = m->getSummonAmount();
          int slotsAvailable = 5-(int)(cards.size());
          for (int i = 0; i < min(summonAmount, slotsAvailable); ++i) {
            shared_ptr<Minion> tmp = dynamic_pointer_cast<Minion>(Card::load(m->getSummonName()));
            cards.push_back(tmp); // TODO: need to setup state stuff for observer pattern
          }
        }
      } else {
        if (m->getAA() == "Damage") {
          vector<shared_ptr<Minion>> &targetCards = (targetPlayer == 1) ? cardsP1: cardsP2;
          int dmg = m->getAADamage();
          targetCards.at(otherSlot - 1)->changeDefence(-dmg);
        }
      }
      m->changeAction(-1);
      player->changeMana(-1 * m->getAC());
      player->setMana(max(player->getMana(), 0));
  } else {
      cout << "Not enough action points/mana to use an activated ability" << endl;
  }
}


void Board::playCardP1(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerOne->getHand().at(slot - 1);              // slot - 1 becauase vector starts 0, slot starts 1
  vector<shared_ptr<Minion>> &cards = (player == 1) ? cardsP1: cardsP2;
  try {
        if ((playerOne->getMana() - c->getCost() >= 0) || testing) {
          if (otherSlot == -1 && player == -1) {          // if we are playing a card which does not target other things
            if (c->getType() == "Minion") {
              cout << "Playing minion: " << c->getName() << endl;
              cardsP1.push_back(dynamic_pointer_cast<Minion>(c));
              playerOne->setState(State::MinionEnter);
              playerOne->notifyObservers();
              playerTwo->setState(State::MinionEnterOpp);
              playerTwo->notifyObservers();
            } else if (c->getType() == "Spell") {
                dynamic_pointer_cast<Spell>(c)->useSpell(*this, *playerOne, otherSlot);
              cout << "Playing spell: " << c->getName() << endl;
            } else if (c->getType() == "Ritual") {
              setRitual(dynamic_pointer_cast<Ritual>(c), 1);
            }

          } else {
              if (c->getType() == "Enchantment") {
                  shared_ptr<Minion> target = cards[otherSlot-1];
                  if (c->getName() == "Giant Strength") {
                      cards[otherSlot-1] = make_shared<GiantStrength>(GiantStrength(target));
                  } else if (c->getName() == "Enrage") {
                      cards[otherSlot-1] = make_shared<Enrage>(Enrage(target));
                  } else if (c->getName() == "Silence") {
                       cards[otherSlot-1] = make_shared<Silence>(Silence(target));
                  } else if (c->getName() == "Magic Fatigue") {
                       cards[otherSlot-1] = make_shared<MagicFatigue>(MagicFatigue(target));
                  } else if (c->getName() == "Haste") {
                       cards[otherSlot-1] = make_shared<Haste>(Haste(target));
                  }
                  cards[otherSlot-1]->addEnchantment(dynamic_pointer_cast<Enchantment>(c));
              } else if (c->getType() == "Spell") {
                Player &p = (player == 1) ? *playerOne : *playerTwo;
                dynamic_pointer_cast<Spell>(c)->useSpell(*this, p, otherSlot);
              }
          }
          playerOne->changeMana(-1 * c->getCost());
          playerOne->setMana(max(playerOne->getMana(), 0));
          playerOne->getHand().erase(playerOne->getHand().begin() + slot - 1); // must erase 
        } else {
            cout << "Not enough mana" << endl;
        }
  } catch(...) {
      cout << "Invalid card usage" << endl;
  }
}
    

void Board::playCardP2(int slot, int player, int otherSlot) {
  shared_ptr<Card> c = playerTwo->getHand().at(slot - 1); // slot - 1 becauase vector starts 0, slot starts 1
  vector<shared_ptr<Minion>> &cards = (player == 1) ? cardsP1: cardsP2;
  try {
      if ((playerTwo->getMana() - c->getCost() >= 0) || testing) {
          if (otherSlot == -1 && player == -1) {          // if we are playing a card which does not target other things
            if (c->getType() == "Minion") {
              cout << "Playing minion: " << c->getName() << endl;
              cardsP2.push_back(dynamic_pointer_cast<Minion>(c));
              playerTwo->setState(State::MinionEnter);
              playerTwo->notifyObservers();
              playerOne->setState(State::MinionEnterOpp);
              playerOne->notifyObservers();
            } else if (c->getType() == "Spell") {
                dynamic_pointer_cast<Spell>(c)->useSpell(*this, *playerTwo, otherSlot);
            } else if (c->getType() == "Ritual") {
                setRitual(dynamic_pointer_cast<Ritual>(c), 2);
            }
          } else {
              if (c->getType() == "Enchantment") {
                  shared_ptr<Minion> target = cards[otherSlot-1];
                  if (c->getName() == "Giant Strength") {
                      cards[otherSlot-1] = make_shared<GiantStrength>(GiantStrength(target));
                  } else if (c->getName() == "Enrage") {
                      cards[otherSlot-1] = make_shared<Enrage>(Enrage(target));
                  } else if (c->getName() == "Silence") {
                       cards[otherSlot-1] = make_shared<Silence>(Silence(target));
                  } else if (c->getName() == "Magic Fatigue") {
                       cards[otherSlot-1] = make_shared<MagicFatigue>(MagicFatigue(target));
                  } else if (c->getName() == "Haste") {
                       cards[otherSlot-1] = make_shared<Haste>(Haste(target));
                  }               
                  cards[otherSlot-1]->addEnchantment(dynamic_pointer_cast<Enchantment>(c));
              }
              else if (c->getType() == "Spell") {
                Player &p = (player == 1) ? *playerOne : *playerTwo;
                dynamic_pointer_cast<Spell>(c)->useSpell(*this, p, otherSlot);
              }
          }
          playerTwo->changeMana(-1 * c->getCost());
          playerTwo->setMana(max(playerTwo->getMana(), 0));
          playerTwo->getHand().erase(playerTwo->getHand().begin() + slot - 1); // must erase because we used "move" previous line
      } else {
          cout << "Not enough mana" << endl;
      }
  } catch(...) {
      cout << "invalid card usage" << endl;
  }
}

void Board::attackMinion(int currentPlayer, int minion, int otherMinion) {
  int otherPlayer = (currentPlayer == 1 ? 2 : 1);
  shared_ptr<Minion> m1 = getCards(currentPlayer).at(minion - 1);
  shared_ptr<Minion> m2 = getCards(otherPlayer).at(otherMinion - 1);
  if (m1->getAction() > 0) {
    m1->attackMinion(*m2);
    // decrease by one action point
    m1->changeAction(-1);
    if (m1->getDefence() <= 0) toGrave(minion, currentPlayer);
    if (m2->getDefence() <= 0) toGrave(otherMinion, otherPlayer);
  } else {
    cout << "Not enough action points to attack." << endl;
  }
}

void Board::attackPlayer(int currentPlayer, int minion) {
  Player *otherPlayer = (currentPlayer == 1 ? playerTwo : playerOne);
  shared_ptr<Minion> attackingMin = getCards(currentPlayer).at(minion - 1);
  if (attackingMin->getAction() > 0) {
    attackingMin->attackPlayer(*otherPlayer);
    // decrease by one action point
    attackingMin->changeAction(-1);
  } else {
    cout << "Not enough action points to attack." << endl;
  }
}

int min(int a, int b) { return a < b ? a : b; }

void Board::inspect(int currentPlayer, int slot) {
  shared_ptr<Minion> m = getCards(currentPlayer).at(slot - 1);
  vector<shared_ptr<Enchantment>> e = m->getEnchantments();

  // print minion
  for (int i = 0; i < cardHeight; ++i) {
    cout << m->display()[i] << endl;
  }

  // print enchantments
  int numRows = (e.size()%5 == 0) ? e.size()/5 : e.size()/5 + 1;
  int col = 0;
  for (int i = 0; i < numRows; ++i) {                         // print for each row
    for (int j = 0; j < cardHeight; ++j) {                    // for card height
      int ctr = 0;
      for (int k = col; k < min(5*(i+1), e.size()); ++k) {    // print enchantmnets
        cout << e.at(k)->display()[j];
        if (ctr == 4 || e.back() == e.at(k)) { 
          cout << endl;
          ctr = 0;
          continue;
        }
        ctr++;
      }
    }
    col = 5*(i+1);
  }
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

shared_ptr<Ritual> Board::getRitual(int playerNum) {
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

void Board::sendNotification(int player, State s) {
    Player *p = (player == 1) ? playerOne : playerTwo;
    p->setState(s);
    p->notifyObservers();
}


