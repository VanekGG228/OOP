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


void Cat::serializeJson(std::ofstream& out) {
    nlohmann::json j{};
    j["type"] = type;
    j["coords.x"] = coords.x;
    j["coords.y"] = coords.y;
    j["scale.x"] = newScale.x;
    j["scale.y"] = newScale.y;
    out << j.dump(4);
}


Cat::Cat(sf::Vector2f coords, string food, sf::Vector2f scale) :Mammal(coords, food) {
    this->type = 1;
    this->newScale = scale;
    this->name = "img/Cat1.png";
    texture.loadFromFile(name);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 109, 99));
    sprite.setScale(newScale.x, newScale.y);
    sprite.setPosition(coords);
    Y = coords.y;
    clock.restart();
}


void Cat::goLeft(float time) {
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 5) {
        CurrentFrame -= 5;
    }

    sprite.setTextureRect(IntRect(109 * int(CurrentFrame)+109, 0, -109, 99));
    sprite.move(-0.2 * time, 0);
}


void Cat::goRight(float time) {
    CurrentFrame += 0.01 * time;
    if (CurrentFrame > 5) {
        CurrentFrame -= 5;
    }

    sprite.setTextureRect(IntRect(109 * int(CurrentFrame), 0, 109, 99));
    sprite.move(0.2 * time, 0);
}


bool Cat::Jump() {
    int speed = 10;
    float time =speed* clock.getElapsedTime().asSeconds();
    sprite.setPosition(sprite.getPosition().x, Y - JumpSpeed * time + 5* time * time);
    return time<(JumpSpeed/5);
}
