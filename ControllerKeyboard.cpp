#include "ControllerKeyboard.h"

void ControllerKeyboard::control(float time, std::queue<sf::Packet>& packetQueue, sf::RenderWindow& window, DrawPictures* animals, int id)
{
    sf::Packet packet;

    if (window.hasFocus()) {
        int moveto = 0;
        packet << "move";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            animals->GoLeft(time, id);
            moveto = 2;
            packet << moveto << time;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            animals->GoRight(time, id);
            moveto = 3;
            packet << moveto << time;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            animals->GoUp(time, id);
            moveto = 4;
            packet << moveto << time;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            animals->GoDown(time, id);
            moveto = 5;
            packet << moveto << time;
        }

        
        if (packet.getDataSize() != 0 && moveto > 0) {
            packetQueue.push(packet);
        }
    }
}

void ControllerKeyboard::setState(int st)
{
    state = st;
}
