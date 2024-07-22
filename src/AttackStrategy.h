#pragma once
#include <SFML/Graphics.hpp>

class AttackStrategy {
public:
    virtual void attack(sf::Texture* texture, sf::Vector2f position) = 0;
    virtual ~AttackStrategy() = default;
};
