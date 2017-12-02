#include "Minion.h"
#include "Decorator.h"

using namespace std;

Decorator::Decorator(shared_ptr<Minion> minion): minion {minion} {}

Decorator::~Decorator() { delete minion; }
