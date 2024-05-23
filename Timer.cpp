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

void Timer::reset()
{
	clock.restart();
	text.setString(std::to_string(startTime)); 
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
