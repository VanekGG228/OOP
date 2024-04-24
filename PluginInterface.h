#pragma once
#include <SFML/Graphics.hpp>

class PluginInterface {
public:
    virtual void generate_start(std::vector<sf::Vector2f>& food) = 0;
    virtual float genFuncOfFly(int windowSizeX, int windowSizeY, sf::Vector2f pos) = 0;
    virtual sf::Vector2f move(int i) = 0;
    virtual ~PluginInterface() {}
};
