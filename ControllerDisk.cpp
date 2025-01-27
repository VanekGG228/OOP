#include "ControllerDisk.h"

ControllerDisk::ControllerDisk(sf::IpAddress ip, unsigned short port)
    : serverIp(ip), serverPort(port), running(true) {
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done) {
        throw std::runtime_error("Failed to connect to server.");
    }
    std::cout << "Connected to server " << serverIp << ":" << serverPort << "\n";

    handshake();

    workerThread = std::thread(&ControllerDisk::run, this);
}
ControllerDisk::~ControllerDisk()
{
    running = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void ControllerDisk::setState(int st)
{
    state = st;
}

void ControllerDisk::control(float time, std::queue<sf::Packet>& packetQueue, sf::RenderWindow& window, DrawPictures* animals, int id)
{
    sf::Packet packet;
    hasFocus = window.hasFocus();
    if (window.hasFocus()) {       
        int moveto = 0;
        if (q.empty()) {
            return;
        }
        sf::Vector2f pos = q.front();
        q.pop();
        packet << "move";
        if (pos.x > par) {
            animals->GoLeft(time, id);
            moveto = 2;
            packet << moveto << time;
        }
        //else
            if (pos.x < -par) {
            animals->GoRight(time, id);
            moveto = 3;
            packet << moveto << time;
        }
        //else 
                if (pos.y > par) {
            animals->GoUp(time, id);
            moveto = 4;
            packet << moveto << time;
        }
       // else 
                 if (pos.y < -par) {
            animals->GoDown(time, id);
            moveto = 5;
            packet << moveto << time;
        }
        
        if (packet.getDataSize() != 0 && moveto > 0) {
            packetQueue.push(packet);
            std::cout << "Pushed: " << pos.x << "\t"<< pos.y << std::endl;
        }

    }
}

void ControllerDisk::handshake()
{
    sf::Uint8 handshakeValue = 23;
    sf::Uint8 response;

    if (socket.send(&handshakeValue, sizeof(handshakeValue)) != sf::Socket::Done) {
        throw std::runtime_error("Failed to send handshake.");
    }

    std::size_t received;
    if (socket.receive(&response, sizeof(response), received) != sf::Socket::Done || response != handshakeValue) {
        throw std::runtime_error("Handshake failed.");
    }

    std::cout << "Handshake successful.\n";
}

void ControllerDisk::receiveFloat(float& value)
{
    sf::Uint8 buffer[sizeof(float)];
    std::size_t received;

    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Done || received != sizeof(buffer)) {
        throw std::runtime_error("Failed to receive float data.");
    }

    value = *reinterpret_cast<float*>(buffer);
}

void ControllerDisk::run()
{
    try {
        while (running) {


            float x, y, z;
            receiveFloat(x);
            receiveFloat(y);
            receiveFloat(z);
            if (hasFocus && state == 2 && (x > par || x <(-par) || y > par || y < (-par))) {
                q.push(sf::Vector2f{ x, y });
               
            }
            //std::cout << "Received: X=" << x << ", Y=" << y << ", Z=" << z << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
