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

void Horse::serializeJson(std::ofstream& out) {
    nlohmann::json j{};
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
    out << j.dump(4);
}

Horse::Horse(sf::Vector2f coords, string food, sf::Vector2f scale) :Mammal(coords, food) {
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
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 4) {
        CurrentFrame -= 4;
        top += 120;
        top %= 360;
    }

    sprite.setTextureRect(IntRect(150 * int(CurrentFrame)+150, top, -150, 115));
    sprite.move(-0.2 * time, 0);
}


void Horse::goRight(float time) {
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 4) {
        CurrentFrame -= 4;
        top += 120;
        top %= 360;
    }

    sprite.setTextureRect(IntRect(150 * int(CurrentFrame), top, 150, 115));
    sprite.move(0.2 * time, 0);
}


bool Horse::Jump() {
    int speed = 10;
    float time = speed * clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5 * time * time);
    return time < (JumpSpeed / 5);
}