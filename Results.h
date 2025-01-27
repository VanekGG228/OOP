#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Results {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text headerText;
    sf::RectangleShape tableBackground;
    sf::RectangleShape columnLine;
    sf::Text columnHeaders[2];
    std::vector<sf::Text> playerNames;
    std::vector<sf::Text> playerScores;

public:
    Results(sf::RenderWindow& win);
    void setResult(const bool result);

    void addRow(const std::string& player, int score);

    void draw();
};

