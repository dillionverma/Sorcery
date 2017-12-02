#ifndef BASICMINION_H
#define BASICMINION_H
#include <string>
#include <vector>
#include "Card.h"

class Board; class Player;

class BasicMinion: public Minion {
    int attack;
    int defence;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;
    public:
      BasicMinion(std::string name, int cost, std::string info, int attack, int defence, int abilityCost);
      void changeAttack(const int amount);
      void changeDefence(const int amount);
      void changeAC(const int amount); 
      int getAttack() const;
      int getDefence() const;
      int getAC() const;
      int getNumEnchants() const;
      void display() override;
      void attackMinion(Minion &m);
      void attackPlayer(Player &p);
      void notify(Board &b, Player &p, int target = -1) override;
};

#endif
