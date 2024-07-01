#include "Platform.h"

#include <SFML/Graphics.hpp>

    Platform::Platform(sf::Vector2f size, sf::Vector2f position) { //constructor (tamaño, poicion)
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
    }
    void Platform::draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    sf::FloatRect Platform::getBounds() const {
        return shape.getGlobalBounds(); //medidas del rectangulo
    }
