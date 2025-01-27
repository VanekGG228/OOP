#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ControllerBase.h"

class ControllerKeyboard: public ControllerBase
{
private:
    int state = 0;
public:
    ControllerKeyboard() {}

    void control(float time, std::queue<sf::Packet>& packetQueue, sf::RenderWindow& window, DrawPictures* animals, int id) override;


    void setState(int st) override;
};


