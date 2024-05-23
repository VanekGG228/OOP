#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
public:

	Timer(int time, int size, float x, float y);
	void reset();
	void start();
	void update();
	void draw(sf::RenderWindow& win);
	bool getEnd();


private:
	sf::Font font;
	sf::Clock clock;
	sf::Text text;
	int startTime;
	int timeLeft;
	bool theEnd;
	bool isRun;
};

