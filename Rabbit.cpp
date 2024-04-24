#include "Rabbit.h"


void Rabbit::serializeBin(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&type), sizeof(type));
    out.write(reinterpret_cast<char*>(&coords), sizeof(sf::Vector2f));
    out.write(reinterpret_cast<char*>(&newScale), sizeof(sf::Vector2f));
}

Rabbit::Rabbit(sf::Vector2f coords, string food, sf::Vector2f scale) :Mammal(coords, food) {
    this->type = 3;
    this->newScale = scale;
    this->name = "img/Rabbit.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 105, 100));
    sprite.setScale(newScale.x, newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    clock.restart();
}
void Rabbit::serializeJson(std::ofstream& out) {
    nlohmann::json j{};
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
    out << j.dump(4);
}

void Rabbit::resize(sf::Vector2f coords) {
    sf::Vector2f sprPos = sprite.getPosition();
    newScale.x = (coords.x - sprPos.x) / sizeX;
    newScale.y = (coords.y - sprPos.y) / sizeX;
    sprite.setScale(newScale.x, newScale.y);
}

void Rabbit::goLeft(float time) {
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 3) {
        CurrentFrame -= 3;
        top += 100;
        top %= 200;
    }
    sprite.setTextureRect(IntRect(105 * int(CurrentFrame)+105, top, -105, 100));
    sprite.move(-0.2 * time, 0);
}


void Rabbit::goRight(float time) {
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 3) {
        CurrentFrame -= 3;
        top += 100;
        top %= 200;
    }

    sprite.setTextureRect(IntRect(105 * int(CurrentFrame), top, 105, 100));
    sprite.move(0.2 * time, 0);
}


bool Rabbit::Jump() {
    int speed = 10;
    float time = speed * clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5 * time * time);
    return time < (JumpSpeed / 5);
}
