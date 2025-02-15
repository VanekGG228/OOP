#pragma once
#include "Cat.h"
#include "Horse.h"
#include "Rabbit.h"
#include "Parrot.h"



class Factory
{
public:
    Animal* createAnimal(Animal_type type, sf::Vector2f coords,sf::String name ,sf::Vector2f scale = sf::Vector2f{ 1.0f, 1.0f })
    {
        Animal* p;
        switch (type)
        {
        case Cat_t:
            p = new Cat(coords, "meat", scale, name);
            break;
        case Horse_t:
            p = new Horse(coords, "grass", scale, name);
            break;
        case Rabbit_t:
            p = new Rabbit(coords, "brown", scale, name);
            break;
        case Parrot_t:
            p = new Parrot(coords, "Red", sf::Vector2f{ 0.5f, 0.5f }, name);
            break;
        default:
            return nullptr;
        }
        return p;
    };
};

