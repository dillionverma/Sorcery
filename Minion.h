#ifndef MINION_H
#define MINION_H
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Card.h"

class Enchantment;

class Minion: public Card {
    protected:
        std::shared_ptr<Enchantment> enchantments;
        int attack;
        int defence;
        std::string triggeredAbility;
        // "Minions start with zero actions"
        int action = 0;
        int abilityCost;
    public:
      Minion(std::string name, int cost, std::string info, int attack, int defence, std::string triggeredAbility, int abilityCost);
      card_template_t display()=0;
      virtual void changeAttack(const int amount)=0;
      virtual void changeDefence(const int amount)=0;
      virtual void changeAC(const int amount)=0; 
      virtual int getAttack() const=0;
      virtual int getDefence() const=0;
      virtual int getAC() const=0;
      virtual void attackMinion(Minion &m)=0;
      virtual void attackPlayer(Player &p)=0;
      virtual void notify(Board &b, Player &p, int target = -1)=0;
};

#endif
