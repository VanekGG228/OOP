#pragma once
#include <queue>
#include "DrawPictures.h"
class ControllerBase
{
    public:
        virtual ~ControllerBase() = default;

        virtual   void control(float time, std::queue<sf::Packet>& packetQueue, sf::RenderWindow& window, DrawPictures* animals, int id) = 0;
        virtual void setState(int st) = 0;

};

