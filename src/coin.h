#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Platform.h"

class Coin {
private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float frameTime;
    float timeSinceLastFrame;
    bool collected;

public:
    Coin(std::vector<sf::Texture>& textures, std::vector<Platform>& platforms);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isColliding(const sf::FloatRect& other);
    bool isCollected() const { return collected; }
    void setCollected(bool value) { collected = value; }
};

#endif // COIN_H
