#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility> 
#include <cmath>
#include <random>


class Food {
private:
    int width;  
    int height; 
    sf::Vector2f center;
    std::vector<sf::Vector2f> positions;
    const int rad = 250;
    int used = 0;

public:

    Food(int screenWidth, int screenHeight);

    sf::Vector2f moveToOppositeSide(int num);

    std::vector<sf::Vector2f> getPostions();

    void setPosition(size_t index, int x, int y);

    bool isOverlapping(const sf::Vector2f& pos1, const sf::Vector2f& pos2, float minDistance);

    std::vector<sf::Vector2f> generateRandomPoints(
        const sf::Vector2f& center, float circleRadius = 250, float pointRadius = 20, int pointCount = 16);
    
};


