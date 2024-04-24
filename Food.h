#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <string>
class Food
{
public:
	Food(int type, int lib);

	void setPos(float x, float y);
	void setK(float k);
	bool Fly(int windowSizeX = 1920, int windowSizeY = 1080);

	void restartClock();
	void draw(sf::RenderWindow& win);
private:
	int vec = 1;
	sf::Vector2f pos;
	float speed = 20;
	sf::Clock clock;
	float k = 0; 
	sf::Texture texture;
	sf::Sprite  sprite;
};

