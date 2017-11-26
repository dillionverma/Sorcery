#ifndef CARD_H
#define CARD_H
#include <string>


// abstract card class
class Card {
    public:    
    //Deck: The players’ deck is a collection of cards which they may draw from.
    //Hand: The players’ hand is a collection of cards (to a maximum of 5) which
    //      they may play.
    //Graveyard: A player’s graveyard is a collection of minions which have died.
    //Board: A player’s board is a collection of cards which they have played and 
    //       which have not been moved to another zone.
    enum Location{Deck, Hand, Graveyard, Board, None};


    // constructor to initally create cards at beginning of game
    Card(std::string name, int cost, std::string info, Location location);

    // getters for private fields
    std::string getName() const;
    int getCost() const;
    std::string getInfo() const;
    Location getLocation() const;

    virtual void playCard() = 0;
    void changeLocation(Location newLocation);

    protected:
    std::string name;
    int cost;
    std::string info;
    Location location;
    
};

#endif
