#include "TextEffect.h"

TextEffect::TextEffect()
{
    font.loadFromFile("font/troika.otf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
}

void TextEffect::showText(const sf::Vector2f& position, bool t)
{
    sf::Color col;
    this->t = t;
    clock.restart();
    if (t) {
        text.setString("+1");
        col = sf::Color::Green;
    }
    else {
        text.setString("-1");
        col = sf::Color::Red;
    }
    text.setPosition(position);
    text.setFillColor(col);
}

bool TextEffect::update()
{
    alpha -= disappearSpeed * clock.getElapsedTime().asSeconds();
    if (alpha < 0)return false;
    if (t) {
        text.setFillColor(sf::Color(0, 128, 0, static_cast<sf::Uint8>(alpha)));
    }
    else {
        text.setFillColor(sf::Color(255, 0, 0, static_cast<sf::Uint8>(alpha)));
    }
    return true;
}

void TextEffect::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
