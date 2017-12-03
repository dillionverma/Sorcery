#include <string>
#include "Minion.h"

using namespace std;

Minion::Minion(string name, 
               int cost, 
               string info, 
               int attack, 
               int defence, 
               string triggeredAbility, 
               string activatedAbility, 
               int abilityCost, 
               int activatedAbilityDamage, 
               string summonMinion,
               int summonAmount):
            Card{name, cost, info, "Minion"}, 
            attack{attack},
            defence{defence}, 
            triggeredAbility {triggeredAbility}, 
            activatedAbility {activatedAbility}, 
            abilityCost{abilityCost}, 
            activatedAbilityDamage{activatedAbilityDamage}, 
            summonMinion{summonMinion},
            summonAmount{summonAmount}{}

Minion::Minion() {}
