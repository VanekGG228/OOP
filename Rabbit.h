#pragma once
#include "Mammal.h"



class Rabbit : public Mammal {
public:

    Rabbit (sf::Vector2f coords, string plumage, sf::Vector2f scale);
    void serializeBin(std::ofstream& out) override;
    void serializeJson(std::ofstream& out) override;
    void resize(sf::Vector2f coords) override ;
    void goLeft(float time) override;
    void goRight(float time) override;
    bool Jump() override ;

private:
    float CurrentFrame = 0;
    int top = 0;
    const int sizeX =105;
    const int sizeY = 100;
    float Y = 0;
    const float JumpSpeed = 50;

};

