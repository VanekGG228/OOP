#pragma once
#include <SFML/Graphics.hpp>
#include "PluginInterface.h"
#include <windows.h>
#include "Food.h"


typedef PluginInterface* (*CreateGunInstanceFunc)();
class FoodInterface
{
public:
	FoodInterface(int lib) {	
		for (int i = 0; i < 16; ++i) {
			food.push_back(new Food(i % 4,lib));
			x.push_back(sf::Vector2f{ 0,0 });
		}
		getLib(lib);
	}

	void gen() {
		gunInstance->generate_start(x);
		for (int i = 0; i < 16; ++i) {
			food[i]->setPos(x[i].x, x[i].y);
			food[i]->setK(gunInstance->genFuncOfFly(1920,1080,x[i]));
		}
	}
	void moveall() {
		for (int i = 0; i < 16; i++) {
			if (!food[i]->Fly()) {
				sf::Vector2f t = gunInstance->move(i);
				food[i]->restartClock();
				food[i]->setK(gunInstance->genFuncOfFly(1920, 1080, t));
				food[i]->setPos(t.x, t.y);
			}
		}
	}

	void draw(sf::RenderWindow& win) {
		for (int i = 0; i < 16; i++) {
			food[i]->draw(win);
		}
	}

	~FoodInterface() {
		for (int i = 0; i < 16; i++) {
			delete food[i];
		}
		delete gunInstance;
		FreeLibrary(pluginHandle);
	}
private:
	int getLib(int type) {
		LPCWSTR wfilename = L"";
		switch (type) {
		case 1:
			wfilename = L"plugins/GunDll1.dll";
			break;
		case 2:
			wfilename = L"plugins/GunDll2.dll";
			break;
		}
	

		pluginHandle = LoadLibrary(wfilename);

		if (!pluginHandle) {
			return 1;
		}

		CreateGunInstanceFunc createFunc = (CreateGunInstanceFunc)GetProcAddress(pluginHandle, "CreateGunInstance");
		if (createFunc == NULL) {

			FreeLibrary(pluginHandle);
			return 1;
		}

		gunInstance = createFunc();
		if (gunInstance == NULL) {
			FreeLibrary(pluginHandle);
			return 1;
		}

	}
	std::vector<Food*> food;
	std::vector<sf::Vector2f> x;
	int num = 16;
	HMODULE pluginHandle;
	PluginInterface* gunInstance;
};

