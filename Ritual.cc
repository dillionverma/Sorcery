#include <string>
#include "Ritual.h"
#include "Player.h"

using namespace std;

Ritual::Ritual(string name, int cost, string info, int numCharges, int activationCost):
    Card{name, cost, info}, numCharges{numCharges}, activationCost{activationCost} {}

void Ritual::notify(Board &b, Player &p) {
    if (numCharges >= activationCost) {
        effect(b, p);
    }
}

void Ritual::effect(Board &b, Player &p) {
    if (name == "Dark Ritual") {
        if (p.getState() == State::StartTurn) {
            p.gainMana(1);
            numCharges -= activationCost;
        }
    } else if (name == "Aura of Power") {
        if (p.getState() == State::MinionEnter) {
            vector<Minion> *cards;
            if (p.getSide() == 0) {
                cards = b.getCardsP1();
            } else {
                cards = b.getCardsP2();
            }
            (*cards)[cards->size()-1].gainAtk(1);
            (*cards)[cards->size()-1].gainDef(1);
            numCharges -= activationCost;
        }
    } else if (name == "Standstill") {
        int minionsP1 = b.getCardsP1()->size();
        int minionsP2 = b.getCardsP2()->size();
        if (p.getState() == State::MinionEnter) {
            if (p.getSide() == 0) {
                b.toGraveP1(minionsP1);
            } else {
                b.toGraveP2(minionsP2);
            }
            numCharges -= activationCost;
        } else if (p.getState() == State::MinionEnterOpp) {
            if (p.getSide() == 0) {
                b.toGraveP2(minionsP2);
            } else {
                b.toGraveP1(minionsP1);
            }
            numCharges -= activationCost;
        }
    }
}

