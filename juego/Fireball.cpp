#include "Fireball.hpp"

Fireball::Fireball(sf::Texture* tex, sf::IntRect texPos, int own, sf::Vector2f pos, sf::Vector2f dir, int startPow)
    : ownerPlayerNum(own), power(startPow), toBeDestroyed(false), direction(dir), frameCount(0) {
    sprite.setTexture(*tex);
    sprite.setPosition(pos);
    sprite.setTextureRect(texPos);
    sprite.setScale(0.75f, 0.75f);
    if (ownerPlayerNum == 1) {
        sprite.setColor(sf::Color::Blue);
    }
}

void Fireball::update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
    sprite.move(direction);
    frameCount++;
    if (frameCount >= 10) {
        power--;
        frameCount = 0;
    }
    if (power <= 0) {
        toBeDestroyed = true;
    }
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x < 0 || pos.y < 0 || pos.x > SCREEN_WIDTH || pos.y > SCREEN_HEIGHT) {
        toBeDestroyed = true;
    }
}

bool Fireball::isColliding(const sf::FloatRect& other) {
    return sprite.getGlobalBounds().intersects(other);
}

sf::Sprite& Fireball::getSprite() {
    return sprite;
}

int Fireball::getPower() const {
    return power;
}

int Fireball::getOwnerPlayerNum() const {
    return ownerPlayerNum;
}

bool Fireball::getToBeDestroyed() const {
    return toBeDestroyed;
}

void Fireball::setToBeDestroyed(bool val) {
    toBeDestroyed = val;
}
