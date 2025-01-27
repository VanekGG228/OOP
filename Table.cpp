#include "Table.h"
#include <string>
#include <iostream>

Table::Table(float x, float y)
{
    std::vector<int> scores(4, 0); 
    initialize(x, y, scores);
}

Table::Table(float x, float y, std::vector<int> score)
{
    if (score.size() < 4) {
        score.resize(4, 0); 
    }
    initialize(x, y, score);
}

void Table::onNotify(const bool event, int type)
{
    if (event) 
        increaseScore(type);
    else
        decreaseScore(type);
}

void Table::initialize(float x, float y, const std::vector<int>& scores) 
{
    this->scores = scores;
    font.loadFromFile("font/troika.otf");
    std::vector<std::string> categories = { "Cats", "Rabbits", "Horses", "Parrots" };

    for (int i = 0; i < 4; ++i) {
        sf::Text categoryText(categories[i], font, 30);

        categoryText.setPosition(x + 30, y + 20 + i * 50.f);
        categoryTexts.push_back(categoryText);

        sf::Text scoreText(std::to_string(scores[i]), font, 30);
        scoreText.setPosition(x + 200.f, y + 20 + i * 50.f);
        scoreTexts.push_back(scoreText);
    }
    outline.setSize(sf::Vector2f(300.f, 220.f));
    outline.setPosition(x, y);
    outline.setFillColor(sf::Color::Black);
}

void Table::resetScore(int index)
{
    scores = { 0, 0, 0, 0 };
    for (int i = 0; i < 4; ++i) {
        scoreTexts[i].setString(std::to_string(scores[i]));
    }
}

void Table::increaseScore(int index)
{
    scores[index]++;
    scoreTexts[index].setString(std::to_string(scores[index]));
    std::cout <<"SCORE inc\t"<< scores[index]<<"\n";
}

void Table::decreaseScore(int index)
{
    scores[index]--;
    scoreTexts[index].setString(std::to_string(scores[index]));
}

void Table::draw(sf::RenderWindow& window)
{
    window.draw(outline);
    for (int i = 0; i < 4; ++i) {
        window.draw(categoryTexts[i]);
        window.draw(scoreTexts[i]);
    }
}

void Table::finalScore(int winX , int winY )
{
    outline.setSize(sf::Vector2f(600.f, 440.f));
    outline.setPosition((winX - outline.getSize().x)/2, (winY - outline.getSize().y) / 2);
    
    for (int i = 0; i < 4; ++i) {
        float x = outline.getPosition().x;
        float y = outline.getPosition().y;
        categoryTexts[i].setPosition(x + 30, y + 20 + i * 100.f);
        categoryTexts[i].setCharacterSize(60);

        scoreTexts[i].setPosition(x + 400.f, y + 20 + i * 100.f);
        scoreTexts[i].setCharacterSize(60);
    }
}
