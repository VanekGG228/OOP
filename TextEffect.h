#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class TextEffect {
public:
    TextEffect();

    void showText(const sf::Vector2f& position, bool t);

    bool update();

    void draw(sf::RenderWindow& window);

private:
    bool t = false;
    sf::Clock clock;
    sf::Font font;
    sf::Text text;
    const float disappearSpeed = 1;
    float alpha = 255;
};

