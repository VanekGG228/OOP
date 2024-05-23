#pragma once
#include "Animal.h"


class Mammal : public Animal {


public:

    Mammal(sf::Vector2f coords, std::string food);
private:
    void Food();
    std::string food;
};
