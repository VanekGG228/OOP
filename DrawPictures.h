#pragma once
#include <SFML/Graphics.hpp>
#include "Animal.h"
#include "CipherInterface.h"
#include "Network.h"

class DrawPictures
{
public:
	std::vector<Animal*> animals;
	sf::String getName(int i) {
		return animals[i]->getName();
	}
	void add(Animal* anime);

	void draw(sf::RenderWindow& app);

	int getObj(sf::Vector2f coords);

	void genPlayers(std::vector<Client>& clients);
	void GoLeft(float time, int numObj);
	void GoUp(float time, int numObj);
	void GoDown(float time, int numObj); 
	void GoRight(float time, int numObj); 
	bool Jump(int numObj);
	void restartClock(int numObj);
	void setCoords(int i,float x, float y) {
		animals[i]->setPos(x, y);
	}

	sf::Vector2f getCoords(int i) {
		return animals[i]->getCoords();
	}
	void newPos(int objNum, sf::Vector2f coords);



	void del(sf::Vector2f coords);

	void setXY(float x, float y) {
		start_x = x;
		start_y = y;
	}

	~DrawPictures();
private:
	bool getLibCipher(bool t, std::string& outS);
	
	float start_x = 0;
	float start_y = 0;
};

