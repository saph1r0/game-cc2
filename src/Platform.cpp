#include "Platform.hpp"

Platform::Platform(sf::Vector2f size, sf::Vector2f position)
    : size(size), position(position) {
    // Inicializar la forma onc tam y pos
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

