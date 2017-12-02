#ifndef MINION_H
#define MINION_H
#include <string>
#include <vector>
#include "Card.h"

class Board; class Player;

class Minion: public Card {
    int attack;
    int defence;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;
    int numEnchantments = 0;
    public:
      Minion(std::string name, int cost, std::string info, int attack, int defence, int abilityCost);
      void changeAttack(const int amount);
      void changeDefence(const int amount);
      void changeAC(const int amount); 
      void changeEnchants(const int num);
      int getAttack() const;
      int getDefence() const;
      int getAC() const;
      int getNumEnchants() const;
      std::vector<std::string> getEnchants() const;
      void display() override;
      void attackMinion(Minion &m);
      void attackPlayer(Player &p);
      void notify(Board &b, Player &p, int target = -1) override;
};

#endif
