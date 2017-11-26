#include <string>
#include "Card.h"

using namespace std;

Card::Card(string name, int cost, string info, Card::Location location):
     name{name}, cost{cost}, info{info}, location{location} {}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

string Card::getInfo() const {
    return info;
}

Card::Location Card::getLocation() const {
    return location;
}

void Card::changeLocation(Card::Location newLocation) {
    location = newLocation;
}
