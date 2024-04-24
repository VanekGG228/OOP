#pragma once
#include "Cat.h"
#include "Horse.h"
#include "Rabbit.h"
#include "Parrot.h"



class Factory
{
public:
    Animal* createAnimal(Animal_type type, sf::Vector2f coords, sf::Vector2f scale = sf::Vector2f{1.0f, 1.0f})
    {
        Animal* p;
        switch (type)
        {
        case Cat_t:
            p = new Cat(coords, "meat", scale);
            break;
        case Cow_t:
            p = new Horse(coords, "grass", scale);
            break;
        case Eagle_t:
            p = new Rabbit(coords, "brown", scale);
            break;
        case Parrot_t:
            p = new Parrot(coords, "Red", scale);
            break;
        default:
            return nullptr;
        }
        return p;
    };
};

