#pragma once
#include <vector>
#include "Food.h"
#include "PluginInterface.h"

extern "C" __declspec(dllexport) PluginInterface * CreateGunInstance();

class Gun:public PluginInterface
{
public:
	Gun();

	void generate_start() override;
	

	void move() override;

	void draw(sf::RenderWindow& win) override;
	~Gun() override;

private:

	void generate(int number);
	int windowSizeX = 1920;
	int windowSizeY = 1080;
	const int num = 16;
	std::vector<Food*> food;
};

