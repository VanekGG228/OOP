#include "Bird.h"

Bird::Bird(sf::Vector2f coords, std::string plumage) :Animal(coords) {
    this->plumage = plumage;
}
