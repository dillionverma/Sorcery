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
    Card();

    // getters for private fields
    virtual std::string getName() const;
    virtual std::string getInfo() const;
    virtual std::string getType() const;
    int getCost() const;
    static std::shared_ptr<Card> load(std::string cardName); 
    virtual card_template_t display()=0;
  protected:
    std::string name;
    int cost;
    std::string info;
    std::string type;

  //virtual ~Card();
    private:    
    virtual void notify(Board &b, Player &p, int target = -1)=0;
};

#endif
