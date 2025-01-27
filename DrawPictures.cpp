#pragma once
#include "DrawPictures.h"
#include "Factory.h"
#include <windows.h>
typedef CipherInterface* (*CreateGunInstanceFunc)();


void DrawPictures::add(Animal* anime)
{
	if (anime) animals.push_back(anime);

}

void DrawPictures::draw(sf::RenderWindow& app)
{
	for (size_t i = 0; i < animals.size(); ++i) {
		if (animals[i]) {
			//std::cout << float(animals[i]->getSprite()->getPosition().x) << "  " << float(animals[i]->getSprite()->getPosition().y) << std::endl;
			animals[i]->draw(app); 
		}
	}
}

int DrawPictures::getObj(sf::Vector2f coords)
{
	for (int i = 0; i < animals.size(); ++i) {
		if (animals[i]->contain(coords)) {
			return i;
		}
	}
	return -1;

}

void DrawPictures::genPlayers(std::vector<Client>& clients)
{
	int max_id = 0;
	for (const auto& client : clients) {
		if (client.id > max_id) {
			max_id = client.id;
		}
	}

	animals.resize(max_id + 1);
	Factory fact;
	for (const auto& client : clients) {
		animals[client.id] = fact.createAnimal(Animal_type(client.id), sf::Vector2f(start_x*client.id, start_y), client.name);
	}
}

void DrawPictures::GoLeft(float time, int numObj)
{
	if (numObj > -1 && numObj<animals.size()) animals[numObj]->goLeft(time);
}

void DrawPictures::GoUp(float time, int numObj)
{
	if (numObj > -1 && numObj < animals.size()) animals[numObj]->goUp(time);
}
void DrawPictures::GoDown(float time, int numObj)
{
	if (numObj > -1 && numObj < animals.size()) animals[numObj]->goDown(time);
}

void DrawPictures::GoRight(float time, int numObj)
{
	if (numObj > -1 && numObj < animals.size()) animals[numObj]->goRight(time);
}

bool DrawPictures::Jump(int numObj)
{
	if (numObj > -1) return animals[numObj]->Jump();
	return false;
}

void DrawPictures::restartClock(int numObj)
{
	if (numObj > -1) animals[numObj]->restartClock();

}

void DrawPictures::newPos(int objNum, sf::Vector2f coords)
{
	if (objNum >= animals.size()) return;
	animals[objNum]->rePos(coords);

}

void DrawPictures::del(sf::Vector2f coords)
{
	for (int i = animals.size() - 1; i >= 0; --i) {
		if (animals[i]->contain(coords)) {
			delete animals[i];
			animals.erase(animals.begin() + i);
			break;
		}
	}

}

DrawPictures::~DrawPictures()
{
	for (int i = animals.size() - 1; i >= 0; --i) {
		delete animals[i];
		animals.erase(animals.begin() + i);
		break;
	}
}

bool DrawPictures::getLibCipher(bool t, std::string& outS)
{
	LPCWSTR wfilename = L"plugins/CipherDLL.dll";

	HMODULE pluginHandle = LoadLibrary(wfilename);

	if (!pluginHandle) {
		return false;
	}
	CreateGunInstanceFunc createFunc = (CreateGunInstanceFunc)GetProcAddress(pluginHandle, "CreateGunInstance");
	if (createFunc == NULL) {
		FreeLibrary(pluginHandle);
		return false;
	}
	CipherInterface* gunInstance = createFunc();

	if (gunInstance == NULL) {
		FreeLibrary(pluginHandle);
		return false;
	}
	if (t)
		gunInstance->encode(outS);
	else
		gunInstance->decode(outS);
	delete gunInstance;
	FreeLibrary(pluginHandle);
	return true;
}


