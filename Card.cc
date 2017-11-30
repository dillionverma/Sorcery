#include <string>
#include "Card.h"

using namespace std;

Card::Card(string name, int cost, string info, string type):
     name{name}, cost{cost}, info{info}, type{type} {}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

string Card::getInfo() const {
    return info;
}

string Card::getType() const {
  return type;
}
