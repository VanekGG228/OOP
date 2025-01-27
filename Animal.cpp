#include "Animal.h"


Animal::Animal(sf::Vector2f coords, sf::String names) {
    
    this->coords = coords;
    if (!font.loadFromFile("font/troika.otf")) {}
    text.setFont(font); 
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setString(names);
      
}


sf::FloatRect Animal::getBounds()
{
    return sprite.getGlobalBounds();
}

void Animal::rePos(sf::Vector2f coords) {
    sprite.setPosition(coords);
}

void Animal::draw(sf::RenderWindow& win)
{
    win.draw(sprite);
    win.draw(text);
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