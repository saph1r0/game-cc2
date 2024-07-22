#include "Enemy.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Texture* texture, float atkTime, AttackStrategy* strategy)
    : attackTime(atkTime), attackStrategy(strategy) {
    sprite.setTexture(*texture);
}

void Enemy::attack(sf::Texture* fireballTexture) {
    attackStrategy->attack(fireballTexture, sprite.getPosition());
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    attackStrategy->draw(window);
}

void Enemy::update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
    attackStrategy->update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
}

Enemy::~Enemy() {
    delete attackStrategy;
}
