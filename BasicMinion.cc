#include <string>
#include <iostream>
#include <vector>
#include "BasicMinion.h"
#include "Player.h"

using namespace std;

BasicMinion::BasicMinion(string name, int cost, string info, int attack, int defence, 
    string triggeredAbility, string activatedAbility, int abilityCost,int activatedAbilityDamage, 
    string summonMinion, int summonAmount):
    Minion{name, cost, info, attack, defence, triggeredAbility, activatedAbility, abilityCost, 
      activatedAbilityDamage, summonMinion, summonAmount} {} 

void BasicMinion::changeAttack(int amount) { attack += amount; }
void BasicMinion::changeDefence(int amount) { defence += amount; }
void BasicMinion::changeAC(int amount) { abilityCost += amount; }
void BasicMinion::changeAction(const int amount) { action += amount; }

int BasicMinion::getAttack() const { return attack;}
int BasicMinion::getDefence() const { return defence;}
int BasicMinion::getAC() const { return abilityCost; }
int BasicMinion::getAction() const { return action; }
string BasicMinion::getAA() const { return activatedAbility; }
string BasicMinion::getTA() const { return triggeredAbility; }
int BasicMinion::getAADamage() const { return activatedAbilityDamage; }
string BasicMinion::getSummonName() const { return summonMinion; }
int BasicMinion::getSummonAmount() const { return summonAmount; }

void BasicMinion::attackMinion(Minion &m) {
  defence -= m.getAttack();
  m.changeDefence(-attack);
}

void BasicMinion::attackPlayer(Player &p) {
  p.changeHealth( -1 * attack);
}

void BasicMinion::notify(Board &b, Player &p, int target) {
    trigger(b, p);
}

void BasicMinion::trigger(Board &b, Player &p) {
    if (triggeredAbility == "Gain Both") { // Gain +1/+1 when a minion leaves play
        if (p.getState() == State::MinionLeave || p.getState() == State::MinionLeaveOpp) {
            changeAttack(1);
            changeDefence(1);
        }
    } else if (triggeredAbility == "Deal One") { // Deal 1dmg to opponent's played minion
        if (p.getState() == State::MinionEnterOpp) {
            int oppNum = (p.getNum() == 1) ? 2 : 1;
            vector<shared_ptr<Minion>> &minions = b.getCards(oppNum);
            shared_ptr<Minion> target = minions[minions.size()-1];
            target->changeDefence(-1);
            if (target->getDefence() <= 0) {
                b.toGrave(minions.size(), oppNum);
            }
        }
    } else if (triggeredAbility == "Gain Defence") { // All minions gain +0/+1 at the end of your turn
        if (p.getState() == State::EndTurn) {
            vector<shared_ptr<Minion>> cards = b.getCards(p.getNum());
            for(auto minion : cards) {
                minion->changeDefence(1);
            }
        }
    }
}

card_template_t BasicMinion::display() {
    if (!triggeredAbility.empty()) {
      return display_minion_triggered_ability(name, cost, attack, defence, info);
    } else if(!activatedAbility.empty()) {
      return display_minion_activated_ability(name, cost, attack, defence, abilityCost, info);
    } else {
      return display_minion_no_ability(name, cost, attack, defence);
    }
}
