#pragma once
#include "Mammal.h"



class Horse : public Mammal {
public:

    Horse(sf::Vector2f coords, string food, sf::Vector2f scale);
    void serializeBin(std::ofstream& out) override;
    void serializeJson(std::ofstream& out) override;
    void resize(sf::Vector2f coords) override;
    void goLeft(float time) override;
    void goRight(float time) override;
    bool Jump() override;
private:
    float CurrentFrame = 0;
    int top = 0;
    const int sizeX = 150;
    const int sizeY = 150;
    float Y = 0;
    const float JumpSpeed = 50;
};