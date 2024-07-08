#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Fireball.h"
#include "Platform.h"
//#include "CollisionManager.h"

class Player{
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
     int itemCount=0;

public:
    Player(const std::string& textureFileRight, const std::string& textureFileLeft, sf::Vector2f position, int number);
    void update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    void resolveCollision(Player& other);
    void resolvePlatformCollision(const Platform& platform);
    
    void shoot(sf::Texture* fireballTexture, sf::Vector2f direction);
    void handleInput(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key attackKey, sf::Texture* fireballTexture);
    bool isColliding(const sf::FloatRect& other);
    std::vector<Fireball>& getFireballs();
    void increaseCollisionCount();
    int getCollisionCount() const;
    void collectItem(); 
    int getItemCount() const; 
};

#endif // PLAYER_H
