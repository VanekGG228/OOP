#include "Cat.h"

void Cat::resize(sf::Vector2f coords) {
    sf::Vector2f sprPos = sprite.getPosition();
    newScale.x = (coords.x - sprPos.x) / sizeX;
    newScale.y = (coords.y - sprPos.y) / sizeX;
    sprite.setScale(newScale.x, newScale.y);
}

void Cat::serializeBin(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&type), sizeof(type));
    out.write(reinterpret_cast<char*>(&coords), sizeof(sf::Vector2f));
    out.write(reinterpret_cast<char*>(&newScale), sizeof(sf::Vector2f));
}


void Cat::serializeJson(nlohmann::json& j) {
    sf::Vector2f coords = sprite.getPosition();
    sf::Vector2f newScale = sprite.getScale();
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
}


Cat::Cat(sf::Vector2f coords, std::string food, sf::Vector2f scale, sf::String names) :Mammal(coords, food, names) {
    this->type = 0;
    this->newScale = scale;
    this->name = "img/Cat1.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 109, 99));
    sprite.setScale(newScale.x, newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    sf::IntRect textureRect = sprite.getTextureRect();
    text.setPosition(coords.x + textureRect.width / 2 - text.getLocalBounds().width / 2, coords.y - textureRect.height / 2 + 10);
    clock.restart();
}


void Cat::goLeft(float time) {
    state = -1;
    animate(-1, time);
    sprite.move(-speed * time, 0);
    text.move(-speed * time, 0);
}


void Cat::goRight(float time) {
    state = 1;
    animate(1, time);
    sprite.move(speed * time, 0);
    text.move(speed * time, 0);
}


bool Cat::Jump() {
    int speed = 10;
    float time =speed* clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5* time * time);
    return time<(JumpSpeed/5);
}

void Cat::goUp(float time)
{
    animate(state,time);
    sprite.move(0, -speed * time);
    text.move(0, -speed * time);
}

void Cat::goDown(float time)
{
    animate(state, time);
    sprite.move(0, speed * time);
    text.move(0, speed * time);
}

void Cat::animate(int state, float time)
{
    CurrentFrame += 0.013 * time;
    if (CurrentFrame > 5) {
        CurrentFrame -= 5;
    }
    int k = 109;
    if (state > 0) k = 0;
    sprite.setTextureRect(sf::IntRect(109 * int(CurrentFrame) + k, 0, state * 109, 99));
}
