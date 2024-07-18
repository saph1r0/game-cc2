#ifndef DEFAULTPLATFORM_HPP
#define DEFAULTPLATFORM_HPP

#include "Platform.hpp"
#include <SFML/Graphics.hpp>

class DefaultPlatform : public Platform {
public:
    DefaultPlatform(sf::Vector2f size, sf::Vector2f position)
        : Platform(size, position) {}

    void draw(sf::RenderWindow& window) override {
        // Implementación básica de dibujo
        sf::RectangleShape shape(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Green); // Color de ejemplo
        window.draw(shape);
    }

    sf::FloatRect getBounds() const override {
        return sf::FloatRect(position, size);
    }
};

#endif

