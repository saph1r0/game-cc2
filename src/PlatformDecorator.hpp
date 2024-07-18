#ifndef PLATFORMDECORATOR_HPP
#define PLATFORMDECORATOR_HPP

#include "Platform.hpp"
#include <SFML/Graphics.hpp>

class PlatformDecorator : public Platform {
protected:
    Platform* decoratedPlatform;

public:
    PlatformDecorator(sf::Vector2f size, sf::Vector2f position, Platform* platform = nullptr)
        : Platform(size, position), decoratedPlatform(platform) {}

    virtual ~PlatformDecorator() {
        // Liberar la memoria si es necesario
        if (decoratedPlatform) {
            delete decoratedPlatform;
            decoratedPlatform = nullptr; // Importante establecer a nullptr después de eliminarlo
        }
    }

    virtual void draw(sf::RenderWindow& window) override {
        if (decoratedPlatform) {
            decoratedPlatform->draw(window);
        }
    }

    virtual sf::FloatRect getBounds() const override {
        if (decoratedPlatform) {
            return decoratedPlatform->getBounds();
        }
        return sf::FloatRect();
    }
};

#endif

