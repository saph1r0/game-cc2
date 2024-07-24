#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>

class Fireball {
private:
    sf::Sprite sprite;
    int power;
    bool toBeDestroyed;
    int ownerPlayerNum;
    int frameCount;
    sf::Vector2f direction;

public:
    Fireball(sf::Texture* tex, sf::IntRect texPos, int own, sf::Vector2f pos, sf::Vector2f dir, int startPow);
    void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH);
    bool isColliding(const sf::FloatRect& other);
    sf::Sprite& getSprite();
    int getPower() const;
    int getOwnerPlayerNum() const;
    bool getToBeDestroyed() const;
    void setToBeDestroyed(bool val);
    sf::FloatRect getBounds() const;
};

#endif // FIREBALL_H
