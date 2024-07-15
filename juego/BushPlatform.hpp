/*#ifndef BUSHPLATFORM_HPP
#define BUSHPLATFORM_HPP

#include "PlatformDecorator.hpp"

class BushPlatform :  public PlatformDecorator {
private:
    sf::Texture bushTexture;
    sf::Sprite bushSprite;

public:
        BushPlatform(sf::Vector2f size, sf::Vector2f position) : Platform(size, position) {

    //BushPlatform(Platform* platform) : PlatformDecorator(platform) {
        bushTexture.loadFromFile("path/to/bush.png");
        bushSprite.setTexture(bushTexture);
        bushSprite.setPosition(decoratedPlatform->getBounds().left, decoratedPlatform->getBounds().top);
    }

    void draw(sf::RenderWindow& window) override {
        PlatformDecorator::draw(window);
        window.draw(bushSprite);
    }
};

#endif*/