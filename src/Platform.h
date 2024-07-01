#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform {
private:
    sf::RectangleShape shape;

public:
    Platform(sf::Vector2f size, sf::Vector2f position);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

#endif // PLATFORM_H
