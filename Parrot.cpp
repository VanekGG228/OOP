#include "Parrot.h"

Parrot::Parrot(sf::Vector2f coords, string plumage, sf::Vector2f scale) :Bird(coords, plumage) {
    this->type = 4;
    this->newScale= scale;
    this->name = "img/parrotAnime1.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 340, 340));
    sprite.setScale(newScale.x, newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    clock.restart();
}

void Parrot::serializeBin(std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&type), sizeof(type));
    out.write(reinterpret_cast<char*>(&coords), sizeof(sf::Vector2f));
    out.write(reinterpret_cast<char*>(&newScale), sizeof(sf::Vector2f));
}

void Parrot::serializeJson(std::ofstream& out) {
    nlohmann::json j{};
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
    out << j.dump(4);
}

void Parrot::resize(sf::Vector2f coords) {
    sf::Vector2f sprPos = sprite.getPosition();
    newScale.x = (coords.x - sprPos.x) / sizeX;
    newScale.y = (coords.y - sprPos.y) / sizeX;
    sprite.setScale(newScale.x, newScale.y);
}

void Parrot::goLeft(float time) {
    CurrentFrame += 0.005 * time;
    if (CurrentFrame > 3) {
        CurrentFrame -= 3;
        top += 280;
        top %= 840;
    }

    sprite.setTextureRect(IntRect(340 * int(CurrentFrame) + 340, top, -320, 280));
    sprite.move(-0.1 * time, 0);
}


void Parrot::goRight(float time) {
    CurrentFrame += 0.005 * time;
    if (CurrentFrame > 3) {
        CurrentFrame -= 3;
        top += 280;
        top %= 840;
    }

    sprite.setTextureRect(IntRect(340 * int(CurrentFrame), top, 320, 280));
    sprite.move(0.1 * time, 0);
}

bool Parrot::Jump() {
    int speed = 10;
    float time = speed * clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5 * time * time);
    return time < (JumpSpeed / 5);
}