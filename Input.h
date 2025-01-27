#pragma once
#include <SFML/Graphics.hpp>

class InputBox {
public:
    InputBox(float x, float y, float width, float height, std::string label);

    void draw(sf::RenderWindow& window);

    void handleEvent(sf::Event event);

    std::string getInput() const;

private:
    const int max_size = 30;
    sf::Font font;
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
    sf::Text textLabel;
    bool isSelected;
};


