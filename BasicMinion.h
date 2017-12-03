#ifndef BASICMINION_H
#define BASICMINION_H
#include <string>
#include <vector>
#include "Card.h"
#include "Minion.h"

class Board; class Player;

class BasicMinion: public Minion {
    public:
      BasicMinion(std::string name, int cost, std::string info, int attack, int defence, std::string triggeredAbility, int abilityCost);
      card_template_t display() override;
      void changeAttack(const int amount) override;
      void changeDefence(const int amount) override;
      void changeAC(const int amount) override; 
      int getAttack() const override;
      int getDefence() const override;
      int getAC() const override;
      void attackMinion(Minion &m) override;
      void attackPlayer(Player &p) override;
      void notify(Board &b, Player &p, int target = -1) override;
      void trigger(Board &b, Player &p);
};

#endif
