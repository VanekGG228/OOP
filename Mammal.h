#pragma once
#include "Animal.h"


class Mammal : public Animal {


public:

    Mammal(sf::Vector2f coords, string food);
private:
    void Food();
    string food;
};
