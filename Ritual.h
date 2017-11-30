#ifndef RITUAL_H
#define RITUAL_H
#include <string>
#include "Card.h"
#include "State.h"

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
      void setNC(const int newNC);
      void setAC(const int newAC);
      void display() override;
};
#endif
