#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Fireball.h"
#include "Platform.h"

enum class PlayerState {
    Idle,
    Running,
    Jumping
};

class Player {
private:
    sf::Sprite sprite;
    sf::Texture textureRight;
    sf::Texture textureLeft;
    sf::Vector2f velocity;
    std::vector<Fireball> fireballs;
    int playerNumber;
    int collisionCount;

    std::vector<sf::IntRect> runningFrames;
    std::vector<sf::IntRect> jumpingFrames;
    int currentFrame;
    float frameTime;
    float timeSinceLastFrame;
    bool isJumping;

public:
    Player(const std::string& textureFileRight, const std::string& textureFileLeft, sf::Vector2f position, int number);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key attackKey, sf::Texture* fireballTexture);
    void resolvePlatformCollision(const Platform& platform);
    void resolveCollision(Player& other);
    void shoot(sf::Texture* fireballTexture, sf::Vector2f direction);

    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;
    std::vector<Fireball>& getFireballs();
    int getCollisionCount() const;
    void increaseCollisionCount();
};

#endif // PLAYER_H
