#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
public:

	Timer(int time, int size, float x, float y);
	void setStartTime(int time);
	void reset();
	void start();
	void update();
	void draw(sf::RenderWindow& win);
	bool getEnd();
	std::string getTime() {
		return text.getString();
	}


private:
	sf::Font font;
	sf::Clock clock;
	sf::Text text;
	int startTime;
	int timeLeft;
	bool theEnd;
	bool isRun;
};

