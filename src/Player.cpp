#include "Player.h"

#include<iostream>

const float GRAVITY = 980.0f;
const float JUMP_SPEED = -450.0f;
const float MOVE_SPEED = 200.0f;


    Player::Player(const std::string& textureFileRight, const std::string& textureFileLeft, sf::Vector2f position, int number)
        : velocity(0.0f, 0.0f), isJumping(false), currentFrame(0), frameTime(0.09f), timeSinceLastFrame(0.0f), shootTimer(0), ammo(5), playerNumber(number)
    {
        textureRight.loadFromFile(textureFileRight);
        textureLeft.loadFromFile(textureFileLeft);
        sprite.setTexture(textureRight);
        sprite.setPosition(position);
        sprite.setScale(3.0f, 4.0f);
        for (int i = 0; i < 4; ++i) {
            int x = 96 + i * 24;
            runningFrames.push_back(sf::IntRect(x+6, 30, 14, 18));
        }
        for (int i = 0; i < 8; ++i) {
            int x = 0 + i * 24;
            jumpingFrames.push_back(sf::IntRect(+6, 78, 14, 18));
        }
        sprite.setTextureRect(runningFrames[currentFrame]);
    }
    void Player::handleInput(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key attackKey, sf::Texture* fireballTexture) {
        if (sf::Keyboard::isKeyPressed(leftKey)) {
            velocity.x = -MOVE_SPEED;
            sprite.setTexture(textureLeft);
        } else if (sf::Keyboard::isKeyPressed(rightKey)) {
            velocity.x = MOVE_SPEED;
            sprite.setTexture(textureRight);
        } else {
            velocity.x = 0;
        }

        if (sf::Keyboard::isKeyPressed(jumpKey) && !isJumping) {
            velocity.y = JUMP_SPEED;
            isJumping = true;
            sprite.setTextureRect(jumpingFrames[currentFrame]);
        }

        if (sf::Keyboard::isKeyPressed(attackKey)) {
            sf::Vector2f fireballDirection;
            if (sprite.getTexture() == &textureRight) {
                fireballDirection = sf::Vector2f(1.0f, 0.0f);
            } else {
                fireballDirection = sf::Vector2f(-1.0f, 0.0f);
            }
            shoot(fireballTexture, fireballDirection);
        }
       

    }

    void Player::shoot(sf::Texture* fireballTexture, sf::Vector2f direction) {
        int startPower = 10;
        if (ammo > 0) {
            if (shootTimer >= 40) {
                sf::Vector2u fireballSize = fireballTexture->getSize();
                fireballSize.x /= 8;
                fireballSize.y /= 8;

                sf::IntRect chosenFireball;
                if (direction.x > 0) {
                    chosenFireball = sf::IntRect(0, 4 * fireballSize.y, fireballSize.x, fireballSize.y);
                } else {
                    chosenFireball = sf::IntRect(0, 0, fireballSize.x, fireballSize.y);
                }
                fireballs.push_back(Fireball(fireballTexture, chosenFireball, playerNumber, sprite.getPosition(), direction, startPower));
                ammo--;
                shootTimer = 0;
            }
        } else {
            ammo = 5;
        }
    }
    void Player::update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        if (isJumping) {
            velocity.y += GRAVITY * deltaTime;
        }
        sprite.move(velocity * deltaTime);

        sf::Vector2f pos = sprite.getPosition();


        if (pos.y + sprite.getGlobalBounds().height >= SCREEN_HEIGHT) {
            sprite.setPosition(pos.x, SCREEN_HEIGHT - sprite.getGlobalBounds().height);
            velocity.y = 0;
            isJumping = false;
            sprite.setTextureRect(runningFrames[currentFrame]);
        }

        if (pos.x < 0) { //creo que aqui esta el error de los costados de caida
            sprite.setPosition(0, pos.y);
        } else if (pos.x + sprite.getGlobalBounds().width >= SCREEN_WIDTH) {
            sprite.setPosition(SCREEN_WIDTH - sprite.getGlobalBounds().width, pos.y);
            velocity.x = 0;
            sprite.setTextureRect(runningFrames[currentFrame]);
        }


        if (velocity.x != 0) {
            timeSinceLastFrame += deltaTime;
            if (timeSinceLastFrame >= frameTime) {
                currentFrame = (currentFrame + 1) % runningFrames.size();
                sprite.setTextureRect(runningFrames[currentFrame]);
                timeSinceLastFrame = 0.0f;
            }
        }
        shootTimer++; ///si llega a 40 espera algo //FALTA

        for (auto& fireball : fireballs) {
            fireball.update(deltaTime);
        }
        fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& fb) { return fb.getToBeDestroyed(); }), fireballs.end());
    }

    void Player::draw(sf::RenderWindow& window) {
        window.draw(sprite);
        for (auto& fireball : fireballs) {
            window.draw(fireball.getSprite());
        }
    }

    sf::FloatRect Player::getBounds() const {
        return sprite.getGlobalBounds();
    }
///////////////////////OBSERVER///////////////////////////////////////////////////////////////
    void Player::collisionCounter(int collision){
        collisionCount = collision;
    }
    void Player::itemCounter(int item){
        itemCount = item;
    }
//////////////////////////////////////////////////////////////////////////////////////

    void Player::resolvePlatformCollision(const Platform& platform) {
        if (getBounds().intersects(platform.getBounds())) {
            sf::FloatRect playerBounds = getBounds();
            sf::FloatRect platformBounds = platform.getBounds();
            sf::Vector2f pos = sprite.getPosition();

            if (playerBounds.top + playerBounds.height -20 < platformBounds.top) {  //pisar
                sprite.setPosition(pos.x, platformBounds.top - playerBounds.height);
                velocity.y = 0;
                isJumping = false;
            }
            else if (playerBounds.top < platformBounds.top + platformBounds.height && //si player pos y es menor a platform pos y + su altura YY player pos y es mayor a platform pos y
                playerBounds.top > platformBounds.top &&
                velocity.y < 0) {
                sprite.setPosition(pos.x, platformBounds.top + platformBounds.height); //techo
                velocity.y = 0;
            }
            else if (playerBounds.left + playerBounds.width > platformBounds.left &&
                playerBounds.left < platformBounds.left + platformBounds.width &&
                playerBounds.top + playerBounds.height > platformBounds.top) {
                if (velocity.x > 0) {
                    sprite.setPosition(platformBounds.left - playerBounds.width, pos.y);
                }
                else if (velocity.x < 0) {
                    sprite.setPosition(platformBounds.left + platformBounds.width, pos.y);
                }
                velocity.x = 0;
            }
        }else {
            // Si no hay colisión, permitir que el jugador caiga si está en el aire
            if (!isJumping && velocity.y == 0) {
                velocity.y = 300.0f;  
            }
        }
    }

    void Player::resolveCollision(Player& other) {
        if (getBounds().intersects(other.getBounds())) {
            sf::FloatRect thisBounds = getBounds();
            sf::FloatRect otherBounds = other.getBounds();
            sf::Vector2f thisPos = sprite.getPosition();
            sf::Vector2f otherPos = other.sprite.getPosition();

            bool isLandingOnTop = thisBounds.top + thisBounds.height - 5.0f <= otherBounds.top;
            bool isOtherOnTop = otherBounds.top + otherBounds.height - 5.0f <= thisBounds.top;

            //colision vertical

            if (velocity.y > 0 && isLandingOnTop) {
                sprite.setPosition(thisPos.x, otherBounds.top - thisBounds.height);
                velocity.y = 0;
                isJumping = false;
            }else if (velocity.y < 0 && isOtherOnTop) {
                other.sprite.setPosition(otherPos.x, thisBounds.top - otherBounds.height);
                other.velocity.y = 0;
                other.isJumping = false;
            }
            //colision horizontal

            if (velocity.x > 0) {
                if (!isLandingOnTop) {
                    sprite.setPosition(otherBounds.left - thisBounds.width, thisPos.y);
                    velocity.x = 0;
                }
            } else if (velocity.x < 0) {
                if (!isLandingOnTop) {
                    sprite.setPosition(otherBounds.left + otherBounds.width, thisPos.y);
                    velocity.x = 0;
                }
            }

        }
    }


    std::vector<Fireball>& Player::getFireballs() {
        return fireballs;
    }

    bool Player::isColliding(const sf::FloatRect& other) {
        return sprite.getGlobalBounds().intersects(other);
    }
