#pragma once
#include <SFML/Graphics.hpp>
#include "AttackStrategy.h"

class Enemy {
protected:
    sf::Sprite sprite;
    float attackTime;
    int damage;
    AttackStrategy* attackStrategy;

public:
    Enemy(sf::Texture* texture, float atkTime, AttackStrategy* strategy);

    void attack(sf::Texture* fireballTexture);

    void draw(sf::RenderWindow& window);

    void update(float deltaTime);

    ~Enemy();
};
