#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Fireball.hpp"
#include <vector>
#include "Platform.hpp" // Incluimos Platform.hpp aquí

class Player {
private:
    sf::Sprite sprite;
    sf::Texture textureRight;
    sf::Texture textureLeft;
    sf::Vector2f velocity;
    bool isJumping;
    std::vector<sf::IntRect> runningFrames;
    std::vector<sf::IntRect> jumpingFrames;
    int currentFrame;
    float frameTime;
    float timeSinceLastFrame;
    std::vector<Fireball> fireballs;
    int shootTimer;
    int ammo;
    int playerNumber;
    int collisionCount;

public:
    Player(const std::string& textureFileRight, const std::string& textureFileLeft, sf::Vector2f position, int number);
    void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void resolveCollision(Player& other);
    void resolvePlatformCollision(const Platform& platform);
    void shoot(sf::Texture* fireballTexture, sf::Vector2f direction);
    void handleInput(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key attackKey, sf::Texture* fireballTexture);
    int getAmmo() const;
    int getPlayerNumber() const;
    std::vector<Fireball>& getFireballs();
    int getCollisionCount() const;
    void incrementCollisionCount();
};

#endif // PLAYER_HPP
