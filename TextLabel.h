#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TextLabel {
public:
    enum class Alignment { Left, Center, Right }; 

private:
    sf::Text text;            
    sf::Font font;           
    sf::RectangleShape rect;  
    sf::Color rectColor;      
    Alignment alignment;     
    
    void updateTextPosition() {
        sf::FloatRect textBounds = text.getLocalBounds();
        sf::Vector2f rectPos = rect.getPosition();
        sf::Vector2f rectSize = rect.getSize();
        float x = rectPos.x; 

        switch (alignment) {
        case Alignment::Left:
            x = rectPos.x - textBounds.left + 10; 
            break;
        case Alignment::Center:
            x = rectPos.x + (rectSize.x - textBounds.width) / 2 - textBounds.left;
            break;
        case Alignment::Right:
            x = rectPos.x + rectSize.x - textBounds.width - textBounds.left - 10; // Отступ 10 пикселей
            break;
        }

        float y = rectPos.y + (rectSize.y - textBounds.height) / 2 - textBounds.top; // По вертикали всегда центрируем
        text.setPosition(x, y);
    }

public:
    TextLabel(const std::string& content, const std::string& fontPath, unsigned int charSize,
        const sf::Color& textColor, const sf::Color& rectColor, const sf::Vector2f& rectSize,
        const sf::Vector2f& rectPos, Alignment align = Alignment::Center)
        : alignment(align) {
        if (!font.loadFromFile(fontPath)) {
            throw std::runtime_error("Ошибка: не удалось загрузить шрифт из файла " + fontPath);
        }

        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(charSize);
        text.setFillColor(textColor);

        rect.setSize(rectSize);
        rect.setPosition(rectPos);
        rect.setFillColor(rectColor);

        updateTextPosition();
    }

    void setText(const std::string& newText) {
        text.setString(newText);
        updateTextPosition();
    }

    void setTextColor(const sf::Color& newColor) {
        text.setFillColor(newColor);
    }

    void setRectColor(const sf::Color& newColor) {
        rect.setFillColor(newColor);
    }

    void setAlignment(Alignment newAlignment) {
        alignment = newAlignment;
        updateTextPosition();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rect);  
        window.draw(text);  
    }
};
