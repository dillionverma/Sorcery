#include <string>
#include <vector>
#include <iostream>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info):
    Card{name, cost, info, "Spell"} {}

void Spell::notify(Board &b, Player &p, int target) {
    // ensure player can afford to play card
    if (p.getMana() >= cost) {
        effect(b, p, target);
        p.changeMana(-cost);
    } else {
        cout << "You do not have enough magic to play this card." << endl;
    }
}

void blizzard(Board &b, int playerNum) {
    vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
    // decrease damage of all minions for opposing player
    for (unsigned int i = 0; i < minions.size(); i++) {
        // take away 2 damage
        minions.at(i)->changeDefence(-2);                
        // minion moved to graveyard if dead
        if (minions.at(i)->getDefence() <= 0) {
            b.toGrave(i, playerNum);
        }
    }
}

// note in this function, player can represent target player
//      or the current player, depending on the spell.
void Spell::effect(Board &b, Player &p, int target) {
    int playerNum = p.getNum(); 
        // Destroy target minion or ritual
        if (name == "Banish") {
            // if ritual
            if (target == 0) {
                // remove chosen ritual card
                b.setRitual(nullptr, p.getNum());
            } else {
                // if minion, send ith card to grave
                // toGrave takes 1-5 so no need to readjust here
                b.toGrave(target, playerNum);
            }
        }
        // Deal 2 Damage to all minions
       else if (name == "Blizzard") {
            blizzard(b, 1);
            blizzard(b, 2);
        }
        // Destroy the top enchantment on target minion
        else if (name == "Disenchant") {
            // Michelle TODO: After enchantments are implemented
        }
        // Resurrect the top minion in your graveyard and set its
        //    defense to 1
        else if (name ==  "Raise Dead") {
            vector<shared_ptr<Minion>> grave = p.getGrave();
            vector<shared_ptr<Card>> hand = p.getHand();
            if (grave.size() > 0) {
                // most recent minion is at back of grave
                shared_ptr<Minion> minionToRes = grave.back();
                grave.pop_back();
                hand.push_back(minionToRes);
                // set defense to 1
                int minionDefence = minionToRes->getDefence();
                minionToRes->changeDefence(- (minionDefence - 1));
            } else {
                cout << "No minions in graveyard to resurrect." << endl;
            }
        }
        // Your ritual gains 3 recharges
        else if (name ==  "Recharge") {
            shared_ptr<Ritual> ritual = b.getRitual(p.getNum());
                if (ritual != nullptr) {
                    ritual->setNC(3);
                    b.setRitual(ritual, p.getNum());
                } else {
                    cout << "No ritual present." << endl;
                }
        }
        //Return target's minion to its owner's hand
        else if (name ==  "Unsummon") {
            vector<shared_ptr<Card>> &hand = p.getHand();            
            vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
            if ((int)minions.size() >= target) {
                // - 1 to account for vector starting at 0
                shared_ptr<Minion> targetMin = minions.at(target - 1);
                minions.erase(minions.begin() + target - 1);
                hand.push_back(targetMin);
            } else {
                cout << "Invalid target minion. No minion exists in that position." << endl;
            }
       }
   
}
void Spell::display() {
    card_template_t card = display_spell(name, cost, info);
    printCard(card);
}

