#pragma once
#include <SFML/Graphics.hpp>
#include "Observer.h"

class Table :public Observer{
public:
    Table(float x, float y);
    Table(float x, float y, std::vector<int> score);
    void onNotify(const bool event, int type) override;
    void resetScore(int index);
    void increaseScore(int index);
    void decreaseScore(int index);
    void draw(sf::RenderWindow& window);

    void finalScore(int winX, int winY);

private:
    void initialize(float x, float y, const std::vector<int>& scores);
    sf::Font font;
    std::vector<int> scores;
    std::vector<sf::Text> categoryTexts;
    std::vector<sf::Text> scoreTexts;
    sf::RectangleShape outline;
};

