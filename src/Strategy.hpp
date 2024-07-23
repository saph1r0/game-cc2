#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "Fireball.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Strategy {
public:
    virtual void shoot(sf::Texture* fireballTexture, sf::Sprite& shape, std::vector<Fireball>& fireballs) = 0;
    virtual void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH, std::vector<Fireball>& fireballs) = 0;
};

class fireballNormal : public Strategy {
    private:
    int ritmo;
public:
    fireballNormal(){ritmo=0;}
    void shoot(sf::Texture* fireballTexture, sf::Sprite& shape, std::vector<Fireball>& fireballs) override {
        if(ritmo==100){
            ritmo = 0;
            sf::Vector2f direction = sf::Vector2f(1.0f, 0.0f);
            int startPower = 10;
            sf::Vector2u fireballSize = fireballTexture->getSize();
            fireballSize.x /= 8;
            fireballSize.y /= 8;
            sf::IntRect chosenFireball;
            if (direction.x > 0) {
                chosenFireball = sf::IntRect(0, 4 * fireballSize.y, fireballSize.x, fireballSize.y);
            } else {
                chosenFireball = sf::IntRect(0, 0, fireballSize.x, fireballSize.y);
            }
            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 1, shape.getPosition(), direction, startPower));
            
        }else{
            ritmo++;
        }
    }

    void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH, std::vector<Fireball>& fireballs) override {
        for (auto& fireball : fireballs) {
            fireball.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
        fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& fb) { return fb.getToBeDestroyed(); }), fireballs.end());
    }
};

//aqui irian copias de fireballNormal pero con mayor velocidad 

class Context {
private:
    sf::Sprite shape;
    std::vector<Fireball> fireballs;
    Strategy* strategy;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;
    sf::Texture textura;
public:
    Context(Strategy* strategy) : strategy(strategy) {
        textura.loadFromFile("/directorio/mine/images/enemy1.png");
        shape.setTexture(textura);
        shape.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-100);
        shape.setScale(4.0f , 4.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        for (auto& fireball : fireballs) {
            window.draw(fireball.getSprite());
        }
    }

    void setStrategy(Strategy* strategy) {
        this->strategy = strategy;
    }

    void executeStrategy(sf::Texture* fireballTexture, float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        strategy->shoot(fireballTexture, shape, fireballs);
        strategy->update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH, fireballs);
    }
};

#endif // STRATEGY_HPP
