#pragma once
#include "Animal.h"


class Mammal : public Animal {


public:

    Mammal(sf::Vector2f coords, std::string food, sf::String names);
private:
    void Food();
    std::string food;
};
