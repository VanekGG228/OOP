#pragma once
#include "FoodInterface.h"
#include "DrawPictures.h"
#include "Table.h"
#include "TextEffect.h"
#include "Subject.h"

class TInteract:public Subject
{
protected:
	static TInteract* interact_;
public:
	TInteract(TInteract& other) = delete;
	void operator = (const TInteract&) = delete;
	static TInteract* getInstance();
	sf::Packet interactObjects(const std::vector<Animal*>& animal, const std::vector<Food*>& food, int id);
	void draw(sf::RenderWindow& win);
	void update();
	void notifyTable(int recieve_num);
	~TInteract();
private:
	TInteract() {};
	
	std::vector < TextEffect* > effects;

};

