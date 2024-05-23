#include "FoodInterface.h"

FoodInterface::FoodInterface(int lib)
{
	for (int i = 0; i < num; ++i) {
		if (lib==1) 
			food.push_back(new Food(i % 4, lib));
		else 
			food.push_back(new Food(4, lib));
		x.push_back(sf::Vector2f{ 0,0 });
	}
	getLib(lib);
}
void FoodInterface::gen()
{
	gunInstance->generate_start(x);
	for (int i = 0; i < num; ++i) {
		food[i]->setPos(x[i].x, x[i].y);
		food[i]->setK(gunInstance->genFuncOfFly(1920, 1080, x[i]));
	}
}

void FoodInterface::moveall()
{
	for (int i = 0; i < num; ++i) {
		if (!food[i]->Fly()) {
			sf::Vector2f t = gunInstance->move(i);
			food[i]->restartClock();
			food[i]->setK(gunInstance->genFuncOfFly(1920, 1080, t));
			food[i]->setPos(t.x, t.y);
		}
	}
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
	delete gunInstance;
	FreeLibrary(pluginHandle);
}

int FoodInterface::getLib(int type)
{
	LPCWSTR wfilename = L"";
	switch (type) {
	case 1:
		wfilename = L"plugins/GunDll.dll";
		break;
	case 2:
		wfilename = L"plugins/GunDll2.dll";
		break;
	}
	pluginHandle = LoadLibraryW(wfilename);

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
