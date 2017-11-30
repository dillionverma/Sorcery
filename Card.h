#ifndef CARD_H
#define CARD_H
#include <string>

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
  protected:
    std::string name;
    int cost;
    std::string info;
    std::string type;

  //virtual ~Card();
  private:    
    virtual void display()=0;
    virtual void notify(Board &b, Player &p)=0;
};

#endif
