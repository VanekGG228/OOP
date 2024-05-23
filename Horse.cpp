#include "Horse.h"

void Horse::serializeBin(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&type), sizeof(type));
    out.write(reinterpret_cast<char*>(&coords), sizeof(sf::Vector2f));
    out.write(reinterpret_cast<char*>(&newScale), sizeof(sf::Vector2f));
}

void Horse::resize(sf::Vector2f coords) {
    sf::Vector2f sprPos = sprite.getPosition();
    newScale.x = (coords.x - sprPos.x) / sizeX;
    newScale.y = (coords.y - sprPos.y) / sizeX;
    sprite.setScale(newScale.x, newScale.y);
}

void Horse::serializeJson(nlohmann::json& j) {
    Vector2f coords = sprite.getPosition();
    Vector2f newScale = sprite.getScale();
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
}

Horse::Horse(sf::Vector2f coords, std::string food, sf::Vector2f scale) :Mammal(coords, food) {
    this->type = 2;
    this->newScale = scale;
    this->name = "img/Horse.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 150, 130));
    sprite.setScale(newScale.x,newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    clock.restart();
}

void Horse::goLeft(float time) {
    state = -1;
    animate(state, time);
    sprite.move(-speed * time, 0);
}


void Horse::goRight(float time) {
    state = 1;
    animate(state, time);
    sprite.move(speed * time, 0);
 
}


bool Horse::Jump() {
    int speed = 10;
    float time = speed * clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5 * time * time);
    return time < (JumpSpeed / 5);
}

void Horse::goUp(float time)
{
    animate(state, time); 
    sprite.move(0, -speed * time); 
}

void Horse::goDown(float time)
{
    animate(state, time);
    sprite.move(0, speed * time);
}

void Horse::animate(int state, float time)
{
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 4) {
        CurrentFrame -= 4;
        top += 120;
        top %= 360;
    }
    int k = 150;
    if (state > 0) k = 0;
    sprite.setTextureRect(IntRect(150 * int(CurrentFrame) + k, top, state * 150, 115));
}
