#pragma once
#include "Bird.h"


class Parrot : public Bird {
public:

    Parrot(sf::Vector2f coords, std::string plumage, sf::Vector2f scale);
    void serializeBin(std::ofstream& out) override;
    void serializeJson(nlohmann::json& j) override;
    void resize(sf::Vector2f coords) override;
    void goLeft(float time) override;
    void goRight(float time) override;
    bool Jump() override;

    void goUp(float time) override;
    void goDown(float time) override;
private:
    void animate(int state, float time);
    float CurrentFrame = 0;
    int top = 0;
    const int sizeX = 340;
    const int sizeY = 340;
    float Y = 0;
    const float JumpSpeed = 50;
    const float speed = 0.24;

};
