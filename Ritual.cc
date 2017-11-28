#include <string>
#include "Ritual.h"
#include "Player.h"

using namespace std;

Ritual::Ritual(string name, int cost, string info, int numCharges, int activationCost):
    Card{name, cost, info}, numCharges{numCharges}, activationCost{activationCost} {}

void Ritual::notify(Player &p) {
    if (numCharges >= activationCost) {
        effect(p);
    }
}

// Concrete Ritual implementations:

DarkRitual::DarkRitual(string name, int cost, string info, int numCharges, int activationCost):
   Ritual{name, cost, info, numCharges, activationCost} {} 

void DarkRitual::effect(Player &p) {
    if (p.getState() == State::StartTurn) {
        p.gainMana(1);
        numCharges -= activationCost;
    }
}

//

AuraOfPower::AuraOfPower(string name, int cost, string info, int numCharges, int activationCost):
   Ritual{name, cost, info, numCharges, activationCost} {} 

void AuraOfPower::effect(Player &p) {
    if (p.getState() == State::MinionEnter) {
        p.minionGainAtk(p.fieldSize()-1, 1);
        p.minionGainDef(p.fieldSize()-1, 1);
        numCharges -= activationCost;
    }
}

//

Standstill::Standstill(string name, int cost, string info, int numCharges, int activationCost):
   Ritual{name, cost, info, numCharges, activationCost} {} 

void Standstill::effect(Player &p) {
    if (p.getState() == State::MinionEnter) {
        p.toGrave(p.fieldSize()-1);
        numCharges -= activationCost;
    } else if (p.getState() == State::MinionEnterOpp) {
        Player *opponent = p.getOpponent();
        opponent->toGrave(opponent->fieldSize()-1);
        numCharges -= activationCost;
    }
}

//





