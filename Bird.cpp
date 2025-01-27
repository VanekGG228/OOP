#include "Bird.h"

Bird::Bird(sf::Vector2f coords, std::string plumage, sf::String names):Animal(coords, names) {
    this->plumage = plumage;
}
