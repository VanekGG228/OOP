#include "Rabbit.h"
#include <iostream>

void Rabbit::serializeBin(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&type), sizeof(type));
    out.write(reinterpret_cast<char*>(&coords), sizeof(sf::Vector2f));
    out.write(reinterpret_cast<char*>(&newScale), sizeof(sf::Vector2f));
}

Rabbit::Rabbit(sf::Vector2f coords, std::string food, sf::Vector2f scale, sf::String names) :Mammal(coords, food, names) {
    this->type = 1;
    this->newScale = scale;
    this->name = "img/Rabbit.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 105, 100));
    sprite.setScale(newScale.x, newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    sf::IntRect textureRect = sprite.getTextureRect();
    text.setPosition(coords.x + textureRect.width / 2 - text.getLocalBounds().width / 2, coords.y - textureRect.height / 2 + 10);
    clock.restart();
}
void Rabbit::serializeJson(nlohmann::json& j) {
    sf::Vector2f coords = sprite.getPosition();
    sf::Vector2f newScale = sprite.getScale();
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;

}

void Rabbit::resize(sf::Vector2f coords) {
    sf::Vector2f sprPos = sprite.getPosition();
    newScale.x = (coords.x - sprPos.x) / sizeX;
    newScale.y = (coords.y - sprPos.y) / sizeX;
    sprite.setScale(newScale.x, newScale.y);
}

void Rabbit::goLeft(float time) {
    state = - 1; 
    animate(state, time); 
    sprite.move(-speed * time, 0);
    text.move(-speed * time, 0);
}


void Rabbit::goRight(float time) {
    state = 1;
    animate(state, time);
    sprite.move(speed * time, 0);
    text.move(speed * time, 0);
}


bool Rabbit::Jump() {
    int speed = 10;
    float time = speed * clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5 * time * time);
    return time < (JumpSpeed / 5);
}

void Rabbit::goUp(float time)
{
    animate(state, time); 
    sprite.move(0, -speed * time);
    text.move(0, -speed * time);
}

void Rabbit::goDown(float time)
{
    animate(state, time); 
    sprite.move(0, speed * time);
    text.move(0, speed * time);
}

void Rabbit::animate(int state, float time)
{
    CurrentFrame += 0.013 * time;
    if (CurrentFrame > 3) {
        CurrentFrame -= 3;
        top += 100;
        top %= 200;
    }
    int k = 105;
    if (state > 0) k = 0;
    sprite.setTextureRect(sf::IntRect(105 * int(CurrentFrame) + k, top, state * 105, 100));
}
