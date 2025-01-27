#pragma once
#include "Mammal.h"



class Rabbit : public Mammal {
public:

    Rabbit (sf::Vector2f coords, std::string plumage, sf::Vector2f scale, sf::String names);
    void serializeBin(std::ofstream& out) override;
    void serializeJson(nlohmann::json& j) override;
    void resize(sf::Vector2f coords) override ;
    void goLeft(float time) override;
    void goRight(float time) override;
    bool Jump() override ;
    void goUp(float time) override;
    void goDown(float time) override;
private:
    void animate(int state, float time);
    float CurrentFrame = 0;
    int top = 0;
    const int sizeX =105;
    const int sizeY = 100;
    float Y = 0;
    const float JumpSpeed = 50;
    const float speed = 0.27;

};

