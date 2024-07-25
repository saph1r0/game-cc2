#ifndef LEVELPLATFORM_HPP
#define LEVELPLATFORM_HPP

#include "PlatformDecorator.hpp"
#include <SFML/Graphics.hpp>
#include "DefaultPlatform.hpp"
#include <iostream>

class LevelPlatform : public PlatformDecorator {
private:
    sf::Texture levelTexture;
    sf::Sprite levelSprite;

public:
    LevelPlatform(sf::Vector2f size, sf::Vector2f position, Platform* platform = nullptr)
        : PlatformDecorator(size, position, platform ? platform : new DefaultPlatform(size, position)) {

        if (!levelTexture.loadFromFile("/home/diogo/Descargas/juego_finall_final/images/Qcmqvn.png")) {
            std::cerr << "Error: Failed to load level texture!" << std::endl;
            exit(EXIT_FAILURE);
        }

        levelSprite.setTexture(levelTexture);
        levelSprite.setPosition(decoratedPlatform->getBounds().left, decoratedPlatform->getBounds().top);
    }

    void draw(sf::RenderWindow& window) override {
        PlatformDecorator::draw(window);
        window.draw(levelSprite);
    }

    bool checkCollision(const sf::FloatRect& playerBounds) {
        return levelSprite.getGlobalBounds().intersects(playerBounds);
    }
};

#endif
