#ifndef MINION_H
#define MINION_H
#include <string>
#include "Card.h"
#include "Ability.h"

class Player;

class Minion: public Card {
    int attack;
    int defence;
    // "Minions start with zero actions"
    int action = 0;
    int abilityCost;

    public:
      Minion(std::string name, int cost, std::string info, int attack, 
          int defense, int abilityCost);
      void changeAttack(const int amount);
      void changeDefence(const int amount);
      int getAttack() const;
      int getDefence() const;
      void display() override;
      void attackMinion(Minion &m);
      void attackPlayer(Player &p);
};

#endif
