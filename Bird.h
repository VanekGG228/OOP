#pragma once
#include "Animal.h"

class Bird : public Animal {
public:

    Bird(sf::Vector2f coords, std::string plumage);

private:
    std::string plumage;

};


