#pragma once
#include "Mammal.h"


class Cat : public Mammal {
public:
    Cat(sf::Vector2f coords, string food, sf::Vector2f scale);
    void serializeBin(std::ofstream &out) override;
    void serializeJson(std::ofstream& out) override ;
    void resize(sf::Vector2f coords) override;
    void goLeft(float time) override;
    void goRight(float time) override;
    bool Jump() override;

private:
    float CurrentFrame = 0;
    const int sizeX = 109;
    const int sizeY = 99;
    float Y = 0;
    const float JumpSpeed = 50;


};

