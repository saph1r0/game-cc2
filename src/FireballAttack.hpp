#ifndef FIREBALLATTACK_HPP
#define FIREBALLATTACK_HPP

#include "AttackStrategy.h"
#include "Fireball.h"
#include <vector>
#include <algorithm>

class FireballAttack : public AttackStrategy {
private:
    std::vector<Fireball*> fireballs;
    sf::Vector2f direction;
    int damage;

public:
    FireballAttack(sf::Vector2f dir, int dmg) : direction(dir), damage(dmg) {}

    void attack(sf::Texture* texture, sf::Vector2f position) override {
        fireballs.push_back(new Fireball(texture, sf::IntRect(0, 0, 32, 32), 0, position, direction, damage));
    }

    void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) override {
        for (auto& fireball : fireballs) {
            fireball->update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
        fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](Fireball* f) { 
            bool destroy = f->getToBeDestroyed();
            if (destroy) delete f;
            return destroy; 
        }), fireballs.end());
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& fireball : fireballs) {
            window.draw(fireball->getSprite());
        }
    }

    ~FireballAttack() {
        for (auto& fireball : fireballs) {
            delete fireball;
        }
    }
};

#endif
