#pragma once
#include "NetworkServer.h"

#include <queue>
#include <thread>
#include <atomic>
#include "Food.h"

class CountdownTimer {
private:
	sf::Clock clock; 
	int duration; 
	int remainingTime; 
	bool running;
	bool was;

public:
	CountdownTimer(int duration) : duration(duration), remainingTime(duration), running(false),was(false) {}

	void reset() {
		was = false;
	}

	void start() {
		clock.restart();
		remainingTime = duration;
		running = true;
		was = true;
	}

	bool update() {
		if (running) {
			remainingTime = duration - static_cast<int>(clock.getElapsedTime().asSeconds());

			if (remainingTime <= 0) {
				remainingTime = 0;
				running = false;
			}
		}
		return was;
	}
	int getRemainingTime() {
		return remainingTime;
	}
	bool isRunning() const {
		return running;
	}
	void setDuration(int dur) {
		duration = dur;
	}
};

class Handler
{
public:
	Handler();
	
	void main_loop();
	~Handler();

private:

	void game();
	void start_game();


	void state1();
	void state2();

	void state3();

	void state4();


	void recieved_data();

	

	void sendQueue();
	Food* food;
	std::atomic<bool> running;
	std::thread send;
	std::thread recieve;
	std::queue<Packet> que;
	unsigned int recieve_num = 0;
	NetworkServer netS;
	int state = 0;
	CountdownTimer* timer;
	int time = 20;
	int GameTime = 60;
	unsigned long long amo = 0;
};

