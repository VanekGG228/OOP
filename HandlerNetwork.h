#pragma once
#include "TInteract.h"
#include "Network.h"
#include "DrawPictures.h"
#include "Results.h"
#include "Timer.h"
#include "ControllerBase.h"
#include <queue>
#include <thread>
#include <atomic>


class HandlerNetwork
{
public:
	HandlerNetwork(sf::IpAddress t_S_Ip, unsigned short t_S_port, std::string clientName, ControllerBase* ctr);

	void recieve_data();
	sf::Socket::Status send_data(sf::Packet packet);

	void main_loop();

	void sendStart();
	void control(float time);
	//void control(float time);

private:

	void sendQueue();
	ControllerBase* controller;
	sf::RenderWindow window;
	Results result;
	FoodInterface food;
	TInteract* interact;
	std::atomic<bool> running{ true };
	DrawPictures animals;
	Timer timer1;
	Timer timer2;
	sf::IpAddress S_Ip;
	unsigned short S_port;
	std::vector<Client> clients;
	NetworkClient netC;
	Table table;
	std::thread catThread;
	std::thread recieveThread;
	std::atomic<int> state = 1;
	int id = 0;
	unsigned long long amo = 0;
	std::queue<sf::Packet> packetQueue; 
	std::thread sendThread;

};

