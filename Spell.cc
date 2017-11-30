#include <string>
#include <vector>
#include <iostream>
#include "Spell.h"

using namespace std;

Spell::Spell(string name, int cost, string info):
    Card{name, cost, info, "spell"} {}

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
    int plrNum = p.getNum(); 
    
        // Destroy target minion or ritual
        if (name == "Banish") {
            // if ritual
            if (target == 0) {
                // remove chosen ritual card
                Ritual *ritual = &b.getRitual(p);
                // remove ritual card on board
                ritual = nullptr;
            } else {
                // if minion, send ith card to grave
                if (plrNum == 1) {
                    b.toGraveP1(target);
                } else {
                    b.toGraveP2(target);
                }
            }
        }
        // Deal 2 Damage to all minions
       else if (name == "Blizzard") {
            // cannot assign reference to nothing so much be done this way
            vector<Minion> &minions = b.getCardsP1();
            if (plrNum == 2) {
                minions = b.getCardsP2();
            }
            // decrease damage of all minions for opposing player
            for (int i = 0; i < minions.size(); i++) {
                int &defVal = minions.at(i).getDef();
                defVal -= 2;
            }
        }
        // Destroy the top enchantment on target minion
        else if (name == "Disenchant") {
            // Michelle TODO: After enchantments are implemented
        }
        // Resurrect the top minion in your graveyard and set its
        //    defense to 1
        else if (name ==  "Raise Dead") {
            vector<Minion> grave = p.getGrave();
            vector<Card *> hand = p.getHand();
            // most recent minion is at back of grave
            Minion minionToRes = grave.back();
            grave.pop_back();
            hand.push_back(&minionToRes);
            // set defense to 1
            int minionDef = minionToRes.getDef();
            minionDef = 1;
        }
        // Your ritual gains 3 recharges
        else if (name ==  "Recharge") {
            Ritual &ritual = b.getRitual(p);
            int numCharge = ritual.getNC();
            numCharge += 3;
        }
        //Return target's minion to its owner's hand
        else if (name ==  "Unsummon") {
            vector<Card *> &hand = p.getHand();            
            vector<Minion> &minions = b.getCardsP1();
            if (plrNum == 2) {
                minions = b.getCardsP2();
            }
            Minion targetMin = minions.at(target);
            minions.erase(minions.begin() + target);
            hand.push_back(&targetMin);
       }
    
void Spell::display() {
}
