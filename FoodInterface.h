#pragma once
#include <SFML/Graphics.hpp>
#include "PluginInterface.h"
#include "Food.h"


typedef PluginInterface* (*CreateGunInstanceFunc)();
class FoodInterface
{
public:
	std::vector<Food*> food;
	FoodInterface(int lib);

	void gen(std::vector<sf::Vector2f> ff);
	void update(int num, float x, float y);

	void draw(sf::RenderWindow& win);

	~FoodInterface();
private:
	std::vector<sf::Vector2f> x;
	int num = 16;
	PluginInterface* gunInstance;
};

