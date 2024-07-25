// Clase Button para manejar botones en SFML
#include <SFML/Graphics.hpp>
#include <iostream>
class Button {
private:
    sf::RectangleShape rect;
    sf::Text textString;
    sf::Vector2f position;
    sf::Vector2f size;
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font)
        : position(position), size(size), textString(text, font, 20) {
        rect.setSize(size);
        rect.setPosition(position);
        rect.setFillColor(sf::Color::Blue);
        //// Set text properties
        textString.setFillColor(sf::Color::White);
        textString.setPosition(position.x + 10, position.y + 10);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rect);
        window.draw(textString);
    }
    /*method checks if a given click position is within the bounds of the button. This is 
    done by comparing the click position with the global bounds of the rectangle.*/
    bool isClicked(sf::Vector2f clickPosition) {
        return rect.getGlobalBounds().contains(clickPosition);
    }


};