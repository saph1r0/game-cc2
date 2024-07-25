#ifndef STRATEGY_HPP
#define STRATEGY_HPP

//#include "Observer.h"
#include "Fireball.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//strategy holds the virtual functions to give us access to whatever class of fireball we choose
class Strategy {
public:
    virtual void shoot(sf::Texture* fireballTexture, sf::Sprite& shape, std::vector<Fireball>& fireballs) = 0;
    virtual void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH, std::vector<Fireball>& fireballs) = 0;
};
//attack that starts in the enemy position
class fireballNormal : public Strategy {
    private:
    int ritmo;
public:
    fireballNormal(){ritmo=0;}
    void shoot(sf::Texture* fireballTexture, sf::Sprite& shape, std::vector<Fireball>& fireballs) override {
        if(ritmo==100){
            ritmo = 0;
            sf::Vector2f direction = sf::Vector2f(2.0f, -1.0f);
            sf::Vector2f direction2 = sf::Vector2f(-1.0f, -1.0f);
            sf::Vector2f directiony = sf::Vector2f(0.0f, -1.0f);
            int startPower = 100;
            sf::Vector2u fireballSize = fireballTexture->getSize();
            fireballSize.x /= 8;
            fireballSize.y /= 8;
            sf::IntRect chosenFireball;
            if (direction.x > 0) {
                chosenFireball = sf::IntRect(0, 3 * fireballSize.y, fireballSize.x, fireballSize.y);
            }

            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, shape.getPosition(), direction, startPower));

            if(direction2.x < 0){
                chosenFireball = sf::IntRect(0, fireballSize.y, fireballSize.x, fireballSize.y);
            }
            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, shape.getPosition(), direction2, startPower));

            if(directiony.y < 0){
                chosenFireball = sf::IntRect(0, 2 * fireballSize.y, fireballSize.x, fireballSize.y);
            }
            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, shape.getPosition(), directiony, startPower));
            
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


//fireballs that start in the borders of the window

class fireballCostados : public Strategy {
    private:
    int ritmo;
public:
    fireballCostados(){ritmo=0;}
    void shoot(sf::Texture* fireballTexture, sf::Sprite& shape, std::vector<Fireball>& fireballs) override {
        if(ritmo==500){
            ritmo = 0;
            sf::Vector2f pos = sf::Vector2f(0,150);
            sf::Vector2f pos2 = sf::Vector2f(1271,300); //window resolutions
            sf::Vector2f pos3 = sf::Vector2f(0,480);

            sf::Vector2f direction = sf::Vector2f(1.0f, 0.0f);
            sf::Vector2f direction2 = sf::Vector2f(-2.0f, 0.0f);
            sf::Vector2f direction3 = sf::Vector2f(0.5f, 0.0f);

            int startPower = 100;
            sf::Vector2u fireballSize = fireballTexture->getSize();
            fireballSize.x /= 8;
            fireballSize.y /= 8;
            sf::IntRect chosenFireball;
            if (direction.x > 0) {
                chosenFireball = sf::IntRect(0, 4 * fireballSize.y, fireballSize.x, fireballSize.y);
            }

            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, pos, direction, startPower));

            if(direction2.x < 0){
                chosenFireball = sf::IntRect(0, 0, fireballSize.x, fireballSize.y);
            }
            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, pos2, direction2, startPower));

            if(direction.x > 0){
                chosenFireball = sf::IntRect(0, 4 * fireballSize.y, fireballSize.x, fireballSize.y);
            }
            fireballs.push_back(Fireball(fireballTexture, chosenFireball, 3, pos3 , direction3, startPower+300));
            
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

//the class context is building the enemy
class Context{ //: public Observer
private:
    sf::Sprite shape;
    std::vector<Fireball> fireballs;
    Strategy* strategy;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;
    sf::Texture textura;
    int collisionCount;
public:
//context set everything to watch the enemy
    Context(Strategy* strategy) : strategy(strategy) {
        textura.loadFromFile("/directorio/game-cc2-juego_actual/images/enemy1.png");
        shape.setTexture(textura);
        shape.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT-100);
        shape.setScale(4.0f , 4.0f);
    }
//draw enemy + fireballs
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        for (auto& fireball : fireballs) {
            window.draw(fireball.getSprite());
        }
    }
//the strategy is the form how the fireballs will look. we can set it insteid of putting it in the constructor
    void setStrategy(Strategy* strategy) {
        this->strategy = strategy;
    }
//for collaing the override funcions
    void executeStrategy(sf::Texture* fireballTexture, float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        strategy->shoot(fireballTexture, shape, fireballs);
        strategy->update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH, fireballs);
    }
/*
///////////////////////OBSERVER///////////////////////////////////////////////////////////////
    void collisionCounter(int collision){
        collisionCount = collision;
    }
//////////////////////////////////////////////////////////////////////////////////////
*/
//to get the fireballs
    std::vector<Fireball>& getFireballs(){
        return fireballs;
    }
};

#endif // STRATEGY_HPP
