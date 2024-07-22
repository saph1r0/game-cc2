#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include <SFML/Graphics.hpp>

class AttackStrategy {
public:
    virtual void attack(sf::Texture* texture, sf::Vector2f position) = 0;
    virtual void draw(sf::RenderWindow& window) = 0; // Añadido el método draw
    virtual void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) = 0; // Añadido el método update
    virtual ~AttackStrategy() = default;
};

#endif
