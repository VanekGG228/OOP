#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "ISerialazable.h"

using namespace sf;

enum Animal_type{ Cat_t = 0, Rabbit_t,Horse_t,Parrot_t };

class Animal:public ISerialazable {
protected:
    sf::Vector2f newScale;
    sf::String name;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f coords;
    Clock clock;
    int type = 0;
    int state = 1;
public:
    int getType();
    sf::Sprite* getSprite();
    virtual void resize(sf::Vector2f coords) = 0;
    virtual void goUp(float time) = 0;
    virtual void goLeft(float time) = 0;
    virtual void goRight(float time) = 0 ;
    virtual void goDown(float time) = 0;
    virtual bool Jump() = 0;
    sf::FloatRect getBounds();


    void restartClock() {clock.restart();}
    void rePos(sf::Vector2f coords);

    bool contain(sf::Vector2f coords);

    sf::Vector2f getCoords();

    sf::Vector2f getScale();
    
    Animal(sf::Vector2f coords);

};
