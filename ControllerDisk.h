#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <queue>
#include <memory>
#include <vector>
#include "ControllerBase.h"
#include <atomic>

class ControllerDisk : public ControllerBase {
public:
    ControllerDisk(sf::IpAddress ip, unsigned short port);

    ~ControllerDisk();
    void setState(int st) override;

    void control(float time, std::queue<sf::Packet>& packetQueue, sf::RenderWindow& window, DrawPictures* animals, int id) override;

private:
    float par = 0.04;
    sf::TcpSocket socket;
    sf::IpAddress serverIp;
    std::queue<sf::Vector2f> q;
    unsigned ping = 3;
    unsigned short serverPort;

    std::thread workerThread; 
    bool running;       
    int state = 0; 
    std::atomic_bool hasFocus;
    void handshake();

    void receiveFloat(float& value);

    void run();
};