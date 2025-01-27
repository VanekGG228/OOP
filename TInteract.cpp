#include "TInteract.h"

TInteract* TInteract::interact_ = nullptr;

TInteract* TInteract::getInstance()
{
	if (interact_ == nullptr) {
		return new TInteract();
	}
	return interact_;
}

sf::Packet TInteract::interactObjects(const std::vector<Animal*>& animal, const std::vector<Food*>& food, int id)
{
	sf::Packet packet;

	for (int i = 0; i < animal.size(); ++i) {
		for (int j = 0; j < food.size(); ++j) {
			if (!animal[i]) continue;
			if (animal[i]->getBounds().intersects(food[j]->getBounds())) {
				//if (animal[i]->getType() == food[j]->getType()) {
					//notify(true, animal[i]->getType());
					effects.push_back(new TextEffect());
					effects[effects.size() - 1]->showText(food[j]->getPos(),true);
					if (i == id){
						packet << "interact" << j;
					}
						
				//}
			/*	else {
					notify(false, animal[i]->getType());
					effects.push_back(new TextEffect());
					effects[effects.size() - 1]->showText(food[j]->getPos(), false);
					packet << "interact" << j << -1;
				}*/
				food[j]->Eaten();
				
			}
		}
	}
	return packet;

}


void TInteract::draw(sf::RenderWindow& win)
{
	
	for (int i = 0; i < effects.size(); ++i) {
	
		effects[i]->draw(win);
	}
}

void TInteract::update()
{
	for (int i = 0; i < effects.size(); ++i) {
		if (!effects[i]->update()) {
			delete effects[i];
			effects.erase(effects.begin() + i);
		}
	}
}

void TInteract::notifyTable(int recieve_num)
{
	notify(true, recieve_num);
}

TInteract::~TInteract()
{
	for (int i = 0; i < effects.size(); ++i) {
			delete effects[i];
			effects.erase(effects.begin() + i);
	}

}
