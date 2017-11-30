#include <string>
#include <iostream>
#include "Ritual.h"
#include "Player.h"

using namespace std;

Ritual::Ritual(string name, int cost, string info, int numCharges, int activationCost):
    Card{name, cost, info, "ritual"}, numCharges{numCharges}, activationCost{activationCost} {}

void Ritual::notify(Board &b, Player &p) {
    if (numCharges >= activationCost) {
        effect(b, p);
    }
}

void Ritual::effect(Board &b, Player &p) {
  int playerNum = p.getNum();

  if (name == "Dark Ritual") {
      if (p.getState() == State::StartTurn) {
          p.changeMana(1);
          numCharges -= activationCost;
      }
  } else if (name == "Aura of Power") {
      if (p.getState() == State::MinionEnter) {
          vector<shared_ptr<Minion>> cards = b.getCards(playerNum);
          cards[cards.size()-1]->changeAttack(1);
          cards[cards.size()-1]->changeDefence(1);
          numCharges -= activationCost;
      }
  } else if (name == "Standstill") {
      int minionsP1 = b.getCards(1).size();
      int minionsP2 = b.getCards(2).size();
      if (p.getState() == State::MinionEnter) {
          if (playerNum == 1) {
              b.toGrave(minionsP1, 1);
          } else {
              b.toGrave(minionsP2, 2);
          }
          numCharges -= activationCost;
      } else if (p.getState() == State::MinionEnterOpp) {
          if (playerNum == 1) {
              b.toGrave(minionsP2, 2);
          } else {
              b.toGrave(minionsP1, 1);
          }
          numCharges -= activationCost;
      }
  }
}

int &Ritual::getNC() {
    return numCharges;
}

int &Ritual::getAC() {
    return activationCost;
}
void Ritual::display() {
    card_template_t card = display_ritual(name, cost, activationCost, info, numCharges);
    printCard(card);
}
