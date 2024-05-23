#pragma once
#include <SFML/Graphics.hpp>

class Food
{
public:
	Food(int type, int lib);
	sf::FloatRect getBounds();
	int getType() {	return type;}
	void setPos(float x, float y);
	sf::Vector2f getPos();

	void setK(float k);
	bool Fly(int windowSizeX = 1920, int windowSizeY = 1080);
	bool Eaten();
	void restartClock();
	void draw(sf::RenderWindow& win);
private:
	int vec = 1;
	int type = 0;
	sf::Vector2f pos;
	float speed = 20;
	sf::Clock clock;
	float k = 0; 
	sf::Texture texture;
	sf::Sprite  sprite;
};

