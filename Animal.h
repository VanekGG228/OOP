#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "ISerialazable.h"

enum Animal_type{ Cat_t = 0, Rabbit_t,Horse_t,Parrot_t };

class Animal:public ISerialazable {
protected:
    sf::Text text;
    sf::Font font;
    sf::Vector2f newScale;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::String name;
    sf::Vector2f coords;
    sf::Clock clock;
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
    void draw(sf::RenderWindow& win);
    bool contain(sf::Vector2f coords);
    void setPos(float x, float y){
        sprite.setPosition(x,y);
    }
    sf::Vector2f getCoords();

    sf::Vector2f getScale();

    sf::String getName() {
        return text.getString();
    }
    
    Animal(sf::Vector2f coords, sf::String names);

    virtual ~Animal(){}
 };
