#pragma once
#include <SFML/Graphics.hpp>
#include "Animal.h"
#include "CipherInterface.h"


class DrawPictures
{
public:
	std::vector<Animal*> animals;

	void add(Animal* anime);

	void draw(sf::RenderWindow& app);

	int getObj(sf::Vector2f coords);

	void genPlayers(int num,int winX, int winY);
	void GoLeft(float time, int numObj);
	void GoUp(float time, int numObj);
	void GoDown(float time, int numObj); 
	void GoRight(float time, int numObj); 
	bool Jump(int numObj);
	void restartClock(int numObj);

	void newPos(int objNum, sf::Vector2f coords);



	void del(sf::Vector2f coords);

	void save(std::ofstream& out);

	void saveJson(std::string& out);

	void load(std::ifstream& in);

	void loadJson(std::string& inS);

	~DrawPictures();
private:
	bool getLibCipher(bool t, std::string& outS);


};

