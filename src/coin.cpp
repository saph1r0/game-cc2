#include "Coin.h"

Coin::Coin(std::vector<sf::Texture>& textures, std::vector<Platform>& platforms)
    : currentFrame(0), frameTime(0.1f), timeSinceLastFrame(0.0f), collected(false)
{
    // Elegir una plataforma aleatoria
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, platforms.size() - 1);
    int platformIndex = dis(gen);
    sf::FloatRect platformBounds = platforms[platformIndex].getBounds();
    float xPos = platformBounds.left + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / platformBounds.width));
    float yPos = platformBounds.top - 20.0f;

    // Configurar el sprite y las animaciones
    for (int i = 0; i < 4; ++i) {
        int x = i * 16;
        frames.push_back(sf::IntRect(x, 0, 16, 16));
    }
    sprite.setTexture(textures[0]);
    sprite.setTextureRect(frames[currentFrame]);
    sprite.setPosition(xPos, yPos);
}

void Coin::update(float deltaTime) {
    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= frameTime) {
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);
        timeSinceLastFrame = 0.0f;
    }
}

void Coin::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Coin::isColliding(const sf::FloatRect& other) {
    return sprite.getGlobalBounds().intersects(other);
}
