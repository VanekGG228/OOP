#pragma once
#include <SFML/Graphics.hpp>

class Food
{
public:
	Food(int type);
	sf::FloatRect getBounds();
	int getType() {	return type;}
	void setPos(float x, float y);
	sf::Vector2f getPos();

	bool Eaten();
	void draw(sf::RenderWindow& win);
private:
	int type = 0;
	sf::Texture texture;
	sf::Sprite  sprite;
};

