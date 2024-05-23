#include "Mammal.h"


Mammal::Mammal(sf::Vector2f coords, std::string food) :Animal(coords) {
    this->food = food;
}

void Mammal::Food() { }