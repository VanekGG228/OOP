#include "Mammal.h"


Mammal::Mammal(sf::Vector2f coords, string food) :Animal(coords) {
    this->food = food;
}

void Mammal::Food() { }