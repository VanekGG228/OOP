#include "Results.h"

Results::Results(sf::RenderWindow& win)
    : window(win) {

    if (!font.loadFromFile("font/troika.otf")) {
        throw std::runtime_error("Failed to load font");
    }

    headerText.setFont(font);
    headerText.setCharacterSize(50);

    headerText.setStyle(sf::Text::Bold);
    headerText.setPosition(window.getSize().x / 2 - 150, 20);

    tableBackground.setSize(sf::Vector2f(400, 300));
    tableBackground.setFillColor(sf::Color(200, 200, 200));
    tableBackground.setOutlineThickness(3);
    tableBackground.setOutlineColor(sf::Color::Black);
    tableBackground.setPosition(window.getSize().x / 2 - 200, 100);

    columnLine.setSize(sf::Vector2f(3, 300));
    columnLine.setFillColor(sf::Color::Black);
    columnLine.setPosition(window.getSize().x / 2, 100);

    std::string headers[] = { "Player", "Score" };
    for (int i = 0; i < 2; ++i) {
        columnHeaders[i].setFont(font);
        columnHeaders[i].setString(headers[i]);
        columnHeaders[i].setCharacterSize(20);
        columnHeaders[i].setFillColor(sf::Color::Black);
        columnHeaders[i].setPosition(window.getSize().x / 2 - 180 + i * 200, 110);
    }
}

void Results::setResult(const bool result)
{
    headerText.setString(result ? "YOU WIN" : "YOU LOSE");
    headerText.setFillColor(result ? sf::Color::Green : sf::Color::Red);
}

void Results::addRow(const std::string& player, int score)
{
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString(player);
    nameText.setCharacterSize(18);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(window.getSize().x / 2 - 180, 150 + playerNames.size() * 30);
    playerNames.push_back(nameText);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(window.getSize().x / 2 + 20, 150 + playerScores.size() * 30);
    playerScores.push_back(scoreText);
}

void Results::draw()
{
    window.draw(tableBackground);
    window.draw(headerText);

    window.draw(columnLine);

    for (auto& header : columnHeaders) {
        window.draw(header);
    }

    for (auto& name : playerNames) {
        window.draw(name);
    }

    for (auto& score : playerScores) {
        window.draw(score);
    }
}
