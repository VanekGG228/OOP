#include "Timer.h"
#include <string>


Timer::Timer(int time,int size, float x,float y):startTime{time},timeLeft{time},isRun{false},theEnd{false}
{
	font.loadFromFile("font/troika.otf");
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Black);
	text.setPosition(x, y);
}

void Timer::setStartTime(int time)
{
	startTime = time;
}

void Timer::reset()
{
	clock.restart();
	text.setString(std::to_string(startTime)); 
	text.setFillColor(sf::Color::Black);
	theEnd = false;
}

void Timer::start()
{
	reset();
	isRun = true;
}


void Timer::update()
{
	if (isRun) {
		timeLeft = startTime - clock.getElapsedTime().asSeconds();
		if (timeLeft <= 5) {
			text.setFillColor(sf::Color::Red);
		}
		if (timeLeft <= 0) {
			text.setString("0");
			isRun = false;
			theEnd = true;
		}
		else {
			text.setString(std::to_string(timeLeft));
			
		}
	}

}

void Timer::draw(sf::RenderWindow& win)
{
	win.draw(text);
}

bool Timer::getEnd()
{
	return theEnd;
}
