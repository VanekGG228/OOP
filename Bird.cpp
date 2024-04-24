#include "Bird.h"

Bird::Bird(sf::Vector2f coords, string plumage) :Animal(coords) {
    this->plumage = plumage;
}
