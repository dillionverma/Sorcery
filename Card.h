#ifndef CARD_H
#define CARD_H
#include <string>
#include "ascii_graphics.h"

class Board; class Player;

// abstract card class
class Card {
  public:    
    // constructor to initally create cards at beginning of game
    Card(std::string name, int cost, std::string info, std::string type);

    // getters for private fields
    std::string getName() const;
    std::string getInfo() const;
    std::string getType() const;
    int getCost() const;
    virtual card_template_t display()=0;
  protected:
    std::string name;
    int cost;
    std::string info;
    std::string type;

  //virtual ~Card();
//  private:    
    public:
    virtual void notify(Board &b, Player &p, int target = -1)=0;
};

#endif
