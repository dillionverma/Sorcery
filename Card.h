#ifndef CARD_H
#define CARD_H
#include <string>


// abstract card class
class Card {
    public:    

    // constructor to initally create cards at beginning of game
    Card(std::string name, int cost, std::string info);

    // getters for private fields
    std::string getName() const;
    int getCost() const;
    std::string getInfo() const;


    protected:
    std::string name;
    int cost;
    std::string info;
    
    private:    
    virtual void display()=0;
};

#endif
