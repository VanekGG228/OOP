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
		app.draw(*(animals[i]->getSprite()));
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

void DrawPictures::genPlayers(int num,int winX, int winY)
{
	Factory fact;
	float pos = winX / 3;
	for (int i = 0; i < num; ++i) {
		pos += i * 100;
		add(fact.createAnimal(Animal_type(i), Vector2f(pos , winY / 3 )));
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

void DrawPictures::save(std::ofstream& out)
{
	for (int i = 0; i < animals.size(); ++i) {
		animals[i]->serializeBin(out);
	}
}

void DrawPictures::saveJson(std::string& outS)
{

	std::ofstream outJ(outS); 
	if (!outJ.is_open()) { 
		return;
	}
	nlohmann::json jsonArray = nlohmann::json::array();

	for (const auto& animal : animals) {
		nlohmann::json j; 
		animal->serializeJson(j); 
		jsonArray.push_back(j); 
	}

	outJ << jsonArray.dump(4);
	outJ.close();

	getLibCipher(true, outS);
}

void DrawPictures::load(std::ifstream& in)
{
	int type = 0;
	Factory fact;
	sf::Vector2f coords;
	sf::Vector2f scale;
	while (in.read(reinterpret_cast<char*> (&type), sizeof(type))) {
		in.read(reinterpret_cast<char*> (&coords), sizeof(coords));
		in.read(reinterpret_cast<char*> (&scale), sizeof(scale));
		Animal* tmp = fact.createAnimal(Animal_type(type), coords, scale);
		add(tmp);
	}
}

void DrawPictures::loadJson(std::string& inS)
{
	std::string tmp("data.r");
	if (!getLibCipher(false, tmp))
		inS = "data.json";
	Factory fact;
	sf::Vector2f coords, scale; 
	std::ifstream in(inS);
	nlohmann::json jsonArray; 
	in >> jsonArray; 
	in.close(); 

	for (const auto& j : jsonArray) {
		
		Vector2f coords{ j["coords.x"], j["coords.y"] };
		Vector2f scale{ j["scale.x"], j["scale.y"] };
		int type = j["type"];
		add(fact.createAnimal(Animal_type(type), coords, scale)); 
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

	HMODULE pluginHandle = LoadLibraryW(wfilename);

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


