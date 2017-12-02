#include "Component.h"
#include "Decorator.h"

Decorator::Decorator(Component *component): component{component} {}

//Decorator::~Decorator() { delete component; }
