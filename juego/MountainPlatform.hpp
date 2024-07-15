#ifndef MOUNTAINPLATFORM_HPP
#define MOUNTAINPLATFORM_HPP

#include "PlatformDecorator.hpp"
#include "DefaultPlatform.hpp"
#include <iostream>

class MountainPlatform : public PlatformDecorator {
private:
    sf::Texture mountainTexture;
    sf::Sprite mountainSprite;

public:
    MountainPlatform(sf::Vector2f size, sf::Vector2f position, Platform* platform = nullptr)
        : PlatformDecorator(size, position, platform ? platform : new DefaultPlatform(size, position)) { // Usar una plataforma predeterminada si platform es nullptr

        if (!mountainTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/Cave - Platforms (copia).png")) {
            std::cerr << "Error: Failed to load mountain texture!" << std::endl;
            exit(EXIT_FAILURE);
        }

        mountainSprite.setTexture(mountainTexture);
        mountainSprite.setPosition(decoratedPlatform->getBounds().left, decoratedPlatform->getBounds().top);
    }

    void draw(sf::RenderWindow& window) override {
        PlatformDecorator::draw(window);
        window.draw(mountainSprite);
    }
};

#endif




