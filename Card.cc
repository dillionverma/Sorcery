#include <string>
#include "Card.h"

using namespace std;

Card::Card(string name, int cost, string info):
     name{name}, cost{cost}, info{info} {}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

string Card::getInfo() const {
    return info;
}

