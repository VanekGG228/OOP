#include "Food.h"


Food::Food(int type, int lib)
{
	std::string path = "img/food" + std::to_string(type) + ".png";
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	switch(lib){
	case 1: {
		speed = 500;
		break;
	}
	case 2:
	{
		speed = 20;
		break;
	}


	}
}

void Food::setPos(float x, float y)
{
		sprite.setPosition(x, y);
		pos = sprite.getPosition();
		vec = 1;
		if (pos.x > 960) vec = -1;
}

void Food::setK(float k)
{
	this->k = k;
}


bool Food::Fly(int windowSizeX, int windowSizeY)
{
	float time = speed * clock.getElapsedTime().asSeconds();
	sprite.setPosition(pos.x + vec * time, pos.y - k * time);
	sf::Vector2f t = sprite.getPosition();
	return (t.x >= 0) && (t.x < windowSizeX) && (t.y >= 0) && (t.y < windowSizeY);
}

void Food::restartClock()
{
	clock.restart();
}

void Food::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
}


