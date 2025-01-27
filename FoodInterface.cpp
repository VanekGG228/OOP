#include "FoodInterface.h"

FoodInterface::FoodInterface(int lib)
{
	for (int i = 0; i < num; ++i) {
		if (lib==1) 
			food.push_back(new Food(i % 4));
		else 
			food.push_back(new Food(4));
		x.push_back(sf::Vector2f{ 0,0 });
	}
}

void FoodInterface::gen(std::vector<sf::Vector2f> ff)
{
	for (int i = 0; i < 16; ++i ) {
		food[i]->setPos(ff[i].x, ff[i].y);
	}
}

void FoodInterface::update(int num,float x, float y)
{
	food[num]->setPos(x, y);
}


void FoodInterface::draw(sf::RenderWindow& win)
{
		for (int i = 0; i < 16; i++) {
			food[i]->draw(win);
		}
}

FoodInterface::~FoodInterface()
{
	for (int i = 0; i < num; i++) {
		delete food[i];
	}
}


