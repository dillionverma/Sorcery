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
        effect(b, p);
    } else {
        cout << "You do not have enough magic to play this card." << endl;
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
                b.setRitual(nullptr, p);
            } else {
                // if minion, send ith card to grave
                b.toGrave(target, playerNum);
            }
        }
        // Deal 2 Damage to all minions
       else if (name == "Blizzard") {
            vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
            // decrease damage of all minions for opposing player
            for (unsigned int i = 0; i < minions.size(); i++) {
                // take away 2 damage
                minions.at(i)->changeDefence(-2);
                // minion moved to graveyard if dead
                if (minions.at(i)->getDefence() <= 0) {
                    b.toGrave(target, playerNum);
                }
            }
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
            // most recent minion is at back of grave
            shared_ptr<Minion> minionToRes = grave.back();
            grave.pop_back();
            hand.push_back(minionToRes);
            // set defense to 1
            int minionDefence = minionToRes->getDefence();
            minionToRes->changeDefence(- (minionDefence - 1));
        }
        // Your ritual gains 3 recharges
        else if (name ==  "Recharge") {
            Ritual ritual = b.getRitual(p);
            ritual.setNC(3);
            b.setRitual(&ritual, p);
        }
        //Return target's minion to its owner's hand
        else if (name ==  "Unsummon") {
            vector<shared_ptr<Card>> &hand = p.getHand();            
            vector<shared_ptr<Minion>> minions = b.getCards(playerNum);
            shared_ptr<Minion> targetMin = minions.at(target);
            minions.erase(minions.begin() + target);
            hand.push_back(targetMin);
       }
   
}
void Spell::display() {
    card_template_t card = display_spell(name, cost, info);
    printCard(card);
}

