#include "Food.h"
#include <random>
#include <string>

Food::Food(int type)
{
	this->type = type; 
	std::string path = "img/food" + std::to_string(type) + ".png";
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setPosition(1921,1921);

}

sf::FloatRect Food::getBounds()
{
	return sprite.getGlobalBounds();
}

void Food::setPos(float x, float y)
{
		sprite.setPosition(x, y);
}

sf::Vector2f Food::getPos()
{
	return sprite.getPosition();
}


bool Food::Eaten()
{
	setPos(1921,1921);
	return true;
}


void Food::draw(sf::RenderWindow& win)
{
	win.draw(sprite);
}


