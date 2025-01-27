#include "Mammal.h"


Mammal::Mammal(sf::Vector2f coords, std::string food, sf::String names) :Animal(coords,  names) {
    this->food = food;
}

void Mammal::Food() { }