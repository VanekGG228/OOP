#include "Animal.h"


Animal::Animal(sf::Vector2f coords) {
    
    this->coords = coords;
      
}


sf::FloatRect Animal::getBounds()
{
    return sprite.getGlobalBounds();
}

void Animal::rePos(sf::Vector2f coords) {
    sprite.setPosition(coords);
}

sf::Vector2f Animal::getScale() {
    return newScale;
}

sf::Vector2f Animal::getCoords() {
    return coords;
}

int Animal::getType()
{
     return type; 
}

sf::Sprite* Animal::getSprite() {
    return &sprite;
};

bool Animal::contain(sf::Vector2f coords) {   

        if (sprite.getGlobalBounds().contains(coords)) {
            return true;
        }
        return false;  
}