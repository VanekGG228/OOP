#pragma once
#include "Animal.h"

class Bird : public Animal {
public:

    Bird(sf::Vector2f coords, string plumage);

private:
    string plumage;

};


