#include "Input.h"

InputBox::InputBox(float x, float y, float width, float height, std::string label)
    : isSelected(false) {
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Green);
    box.setOutlineThickness(2);

    if (!font.loadFromFile("font/troika.otf")) {}
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    text.setPosition(x + 5, y + 5);

    textLabel.setFont(font);
    textLabel.setCharacterSize(34);
    textLabel.setFillColor(sf::Color::Yellow);
    textLabel.setPosition(x, y - 50);
    textLabel.setString(label);
    input = "_";
}

void InputBox::draw(sf::RenderWindow& window)
{
    if (isSelected) {
        box.setFillColor(sf::Color::Magenta);
    }
    else {
        box.setFillColor(sf::Color::White);

    }
    window.draw(box);
    window.draw(text);
    window.draw(textLabel);
}

void InputBox::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            isSelected = true;
            input = input == "_" ? "" : input;
        }
        else {
            isSelected = false;
            if (input.empty()) input = "_";
        }
    }

    if (isSelected && input.size() < max_size && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') {
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

std::string InputBox::getInput() const
{
    return input;
}
