#include "TInteract.h"

TInteract* TInteract::interact_ = nullptr;

TInteract* TInteract::getInstance()
{
	if (interact_ == nullptr) {
		return new TInteract();
	}
	return interact_;
}

int TInteract::interactObjects(const std::vector<Animal*>& animal, const std::vector<Food*>& food)
{

	for (int i = 0; i < animal.size(); ++i) {
		for (int j = 0; j < food.size(); ++j) {
			if (animal[i]->getBounds().intersects(food[j]->getBounds())) {
				if (animal[i]->getType() == food[j]->getType()) {
					notify(true, animal[i]->getType());
					effects.push_back(new TextEffect());
					effects[effects.size() - 1]->showText(food[j]->getPos(),true);
				}
				else {
					notify(false, animal[i]->getType());
					effects.push_back(new TextEffect());
					effects[effects.size() - 1]->showText(food[j]->getPos(), false);
				}
				food[j]->Eaten();

			}
		}
	}
	return 0;

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

TInteract::~TInteract()
{
	for (int i = 0; i < effects.size(); ++i) {
			delete effects[i];
			effects.erase(effects.begin() + i);
	}

}
