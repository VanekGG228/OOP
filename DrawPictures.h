#pragma once
#include <SFML/Graphics.hpp>
#include "Animal.h"
#include <vector>
#include "Factory.h"
#include <map>


class DrawPictures
{
public:
	void add(Animal* anime) {
		if (anime) animals.push_back(anime);

	}

	void draw(sf::RenderWindow &app) {
		for (size_t i = 0; i < animals.size(); ++i) {
			app.draw(*(animals[i]->getSprite()));
		}
	}

	void resize(int objNum,sf::Vector2f coords) {
		if (objNum >= animals.size()) return;
		animals[objNum]->resize(coords);

	}

	int getObj(sf::Vector2f coords) {
		for (int i = 0  ; i < animals.size(); ++i) {
			if (animals[i]->contain(coords)) {
				return i;
			}
		}
		return -1;

	}


	void GoLeft(float time,int numObj) {
		if (numObj > -1) animals[numObj]->goLeft(time);
	}
	void GoRight(float time, int numObj) {
		if (numObj>-1) animals[numObj]->goRight(time);
	}
	bool Jump(int numObj) {
		if (numObj > -1) return animals[numObj]->Jump();
		return false;
	}
	void restartClock( int numObj) {
		if (numObj > -1) animals[numObj]->restartClock();

	}

	void newPos(int objNum, sf::Vector2f coords) {
		if (objNum >= animals.size()) return;
		animals[objNum]->rePos(coords);

	}



	void del(sf::Vector2f coords) {
		for (int i = animals.size()-1; i >=0 ; --i) {
			if (animals[i]->contain(coords)) {
				delete animals[i];
				animals.erase(animals.begin() + i);
				break;
			}
		}

	}

	void save(std::ofstream& out) {
		for (int i = 0; i < animals.size(); ++i) {
			animals[i]->serializeBin(out);
		}
	}

	void saveJson(std::ofstream& out) {
		for (int i = 0; i < animals.size(); ++i) {
			animals[i]->serializeJson(out);
		}
	}



	void load(std::ifstream& in) {
		uint8_t type = 0;
		Factory fact; 
		sf::Vector2f coords;
		sf::Vector2f scale;
		while (in.read(reinterpret_cast<char*> (&type), sizeof(type))){	
			in.read(reinterpret_cast<char*> (&coords), sizeof(coords));
			in.read(reinterpret_cast<char*> (&scale), sizeof(scale));
			Animal* tmp = fact.createAnimal(Animal_type(type-1), coords,scale);
			add(tmp);
		}
	}

	void loadJson(std::ifstream& in) {
		uint8_t type = 0;
		Factory fact;
		sf::Vector2f coords;
		sf::Vector2f scale;
		while (in.peek()!=EOF) {
			nlohmann::json j;
			in >> j;
			int type = j["type"];
			coords = Vector2f{ j["coords.x"], j["coords.y"] };
			scale = Vector2f{ j["scale.x"], j["scale.y"] };	
			add(fact.createAnimal(Animal_type(type-1),coords,scale));

		}
	}

	~DrawPictures(){

		for (int i = animals.size() - 1; i >= 0; --i) {
				delete animals[i];
				animals.erase(animals.begin() + i);
				break;
		}
	}
private:

	std::vector<Animal*> animals;


};

