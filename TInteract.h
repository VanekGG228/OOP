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
	int interactObjects(const std::vector<Animal*>& animal, const std::vector<Food*>& food);
	void draw(sf::RenderWindow& win);
	void update();
	~TInteract();
private:
	TInteract() {};
	
	std::vector < TextEffect* > effects;

};

