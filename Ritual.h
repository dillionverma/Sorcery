#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "Card.h"
#include "State.h"
#include "Minion.h"

class Player; class Board;

class Ritual: public Card {

    int numCharges;
    int activationCost;
    
    public:
      Ritual(std::string name, int cost, std::string info, int numCharges, int activationCost);
      void notify(Board &b, Player &p, int target = -1) override;
      void effect(Board &b, Player &p, int target = -1);
      int getNC() const;
      int getAC() const;
      void changeNC(const int amount);
      void setNC(const int newNC);
      void setAC(const int newAC);
      card_template_t display() override;
};
#endif
