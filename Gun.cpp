#include "Gun.h"


extern "C" __declspec(dllexport) PluginInterface * CreateGunInstance() {
	return new Gun();
}

Gun::Gun()
{
	for (int i = 0; i < num; ++i) {
		food.push_back(new Food(i % 4));
	}
}

void Gun::generate_start()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr1(0.0f, static_cast<float>(windowSizeX));
	std::uniform_real_distribution<> distr2(0.0f, static_cast<float>(windowSizeY));

	for (int i = 0; i < num / 4; ++i) {
		food[i]->setPos(distr1(gen), 0);
		food[i]->genFuncOfFly(windowSizeX, windowSizeY);
	}

	for (int i = num / 4; i < num / 2; ++i) {
		food[i]->setPos(0, distr2(gen));
		food[i]->genFuncOfFly(windowSizeX, windowSizeY);
	}

	for (int i = num / 2; i < 3 * num / 4; ++i) {
		food[i]->setPos(windowSizeX, distr2(gen));
		food[i]->genFuncOfFly(windowSizeX, windowSizeY);
	}

	for (int i = 3 * num / 4; i < num; ++i) {
		food[i]->setPos(distr1(gen), windowSizeY);
		food[i]->genFuncOfFly(windowSizeX, windowSizeY);
	}
}


void Gun::move()
{
	for (int i = 0; i < num; ++i) {
		if (!(food[i]->Fly(windowSizeX, windowSizeY))) {
			generate(i);
			food[i]->genFuncOfFly(windowSizeX, windowSizeY);
			food[i]->restartClock();
		}
	}
}

void Gun::draw(sf::RenderWindow& win)
{
	for (int i = 0; i < num; ++i) {
		food[i]->draw(win);
	}
}

Gun::~Gun()
{
	for (int i = 0; i < num; ++i) {
		delete food[i];
	}
}

void Gun::generate(int number)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr1(0.0f, static_cast<float>(windowSizeX));
	std::uniform_real_distribution<> distr2(0.0f, static_cast<float>(windowSizeY));
	switch (number - number % 4) {
	case 0: {
		food[number]->setPos(distr1(gen), 0);
		break;
	}

	case 4: {
		food[number]->setPos(0, distr2(gen));
		break;
	}
	case 8: {
		food[number]->setPos(windowSizeX, distr2(gen));
		break;
	}
	case 12: {
		food[number]->setPos(distr1(gen), windowSizeY);
		break;
	}
	}
}
