#pragma once
#include <SFML/Graphics.hpp>
#include "PluginInterface.h"
#include <windows.h>
#include "Food.h"


typedef PluginInterface* (*CreateGunInstanceFunc)();
class FoodInterface
{
public:
	std::vector<Food*> food;
	FoodInterface(int lib);

	void gen();
	void moveall();

	void draw(sf::RenderWindow& win);

	~FoodInterface();
private:
	int getLib(int type);
	std::vector<sf::Vector2f> x;
	int num = 16;
	HMODULE pluginHandle;
	PluginInterface* gunInstance;
};

