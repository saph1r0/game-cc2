#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>

class Platform {
protected:
    sf::Vector2f size;
    sf::Vector2f position;
    sf::RectangleShape shape;

public:
    Platform(sf::Vector2f size, sf::Vector2f position);
    virtual ~Platform() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};

#endif



