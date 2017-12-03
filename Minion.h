#ifndef MINION_H
#define MINION_H
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Card.h"

class Minion: public Card {
    int attack;
    int defence;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;
    protected:
        <shared_ptr<Enchantment>> enchantments;
    public:
      Minion(std::string name, int cost, std::string info, int attack, int defence, int abilityCost);
      virtual void changeAttack(const int amount)=0;
      virtual void changeDefence(const int amount)=0;
      virtual void changeAC(const int amount)=0; 
      virtual int getAttack()=0 const;
      virtual int getDefence()=0 const;
      virtual int getAC()=0 const;
      virtual void display() override;
      virtual void attackMinion(Minion &m);
      virtual void attackPlayer(Player &p);
      void notify(Board &b, Player &p, int target = -1) override;
};

#endif
