#include "Player.h"

#include<iostream>

const float GRAVITY = 980.0f;
const float JUMP_SPEED = -450.0f;
const float MOVE_SPEED = 200.0f;

//Constructor Player(texture for right side, texture for left side, vector (x,y) position, number to identify the player and color the fireballs, player name, and font for the name)
    Player::Player(const std::string& textureFileRight, const std::string& textureFileLeft, sf::Vector2f position, int number, const std::string& playerName, const sf::Font& font)
        : velocity(0.0f, 0.0f), isJumping(false), currentFrame(0), frameTime(0.09f), timeSinceLastFrame(0.0f), shootTimer(0), ammo(5), playerNumber(number)
    {
        textureRight.loadFromFile(textureFileRight);
        textureLeft.loadFromFile(textureFileLeft);
        sprite.setTexture(textureRight);
        sprite.setPosition(position);
        sprite.setScale(3.0f, 3.5f);
        //runningframes is constantly updated to make the character "run".
        for (int i = 0; i < 4; ++i) {
            int x = 96 + i * 24;
            runningFrames.push_back(sf::IntRect(x+6, 30, 14, 18));
        }
        for (int i = 0; i < 8; ++i) {
            int x = 0 + i * 24;
            jumpingFrames.push_back(sf::IntRect(+6, 78, 14, 18));
        }
        sprite.setTextureRect(runningFrames[currentFrame]);
    //elements to have the player's name
        playerNameText.setFont(font);
        playerNameText.setString(playerName);
        playerNameText.setCharacterSize(20);
        playerNameText.setFillColor(sf::Color::White);
        updateNamePosition();
    }

    //function for the text to follow the player
    void Player::updateNamePosition() {
        playerNameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20);
    }

    //Function to track which keys are pressed, fireball texture is added because attacñkey is related to the creation of fireballs with shoot.
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

    //function for the creation of fireballs

    void Player::shoot(sf::Texture* fireballTexture, sf::Vector2f direction) {
        //'range' of fireballs to be launched
        int startPower = 10;
        if (ammo > 0) {
            if (shootTimer >= 40) {
                //calculate fireball measurements
                sf::Vector2u fireballSize = fireballTexture->getSize();
                fireballSize.x /= 8;
                fireballSize.y /= 8;

                sf::IntRect chosenFireball;
                // if it goes to the right, choose the texture on the right.
                if (direction.x > 0) {
                    chosenFireball = sf::IntRect(0, 4 * fireballSize.y, fireballSize.x, fireballSize.y);
                } else { // if it goes to the left, choose the texture on the left.
                    chosenFireball = sf::IntRect(0, 0, fireballSize.x, fireballSize.y);
                }
                //the fireballs are being added to a vector
                fireballs.push_back(Fireball(fireballTexture, chosenFireball, playerNumber, sprite.getPosition(), direction, startPower));
                ammo--;
                shootTimer = 0;
            }
        } else {
            ammo = 5;
        }
    }
    
    void Player::update(float deltaTime, int SCREEN_HEIGHT, int SCREEN_WIDTH) {
        // if we press key to jump the variable is true, so multiply gravityen and * deltatime to make it look like jumping.
        if (isJumping) {
            velocity.y += GRAVITY * deltaTime;
        }
        //the sprite moves by multiplying deltatime (changing variable) by the velocity
        sprite.move(velocity * deltaTime);

        sf::Vector2f pos = sprite.getPosition();

    //the next set of ifs are for the character not to go out of the screen, they are the limits.
        if (pos.y + sprite.getGlobalBounds().height >= SCREEN_HEIGHT) {
            sprite.setPosition(pos.x, SCREEN_HEIGHT - sprite.getGlobalBounds().height);
            velocity.y = 0;
            isJumping = false;
            sprite.setTextureRect(runningFrames[currentFrame]);
        }

        if (pos.x < 0) {
            sprite.setPosition(0, pos.y);
        } else if (pos.x + sprite.getGlobalBounds().width >= SCREEN_WIDTH) {
            sprite.setPosition(SCREEN_WIDTH - sprite.getGlobalBounds().width, pos.y);
            velocity.x = 0;
            sprite.setTextureRect(runningFrames[currentFrame]);
        }

        //when the character n moves it calculates a specific texture.
        if (velocity.x != 0) {
            timeSinceLastFrame += deltaTime;
            if (timeSinceLastFrame >= frameTime) {
                currentFrame = (currentFrame + 1) % runningFrames.size();
                sprite.setTextureRect(runningFrames[currentFrame]);
                timeSinceLastFrame = 0.0f;
            }
        }
        shootTimer++;
    //  fireballs are updated, similar to update player logic
        for (auto& fireball : fireballs) {
            fireball.update(deltaTime,SCREEN_HEIGHT,SCREEN_WIDTH);
        }
        //when a certain number of firevalls is reached, they are removed.
        fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& fb) { return fb.getToBeDestroyed(); }), fireballs.end());
        //update of player name is done
        updateNamePosition();
    }
//the fireballs and player+name are drawn on the screen
    void Player::draw(sf::RenderWindow& window) {
        window.draw(sprite);
        window.draw(playerNameText);
        for (auto& fireball : fireballs) {
            window.draw(fireball.getSprite());
        }
    }
//the player is a sprite a sprite has (x,y,width,height), return those measures.
    sf::FloatRect Player::getBounds() const {
        return sprite.getGlobalBounds();
    }
///////////////////////OBSERVER///////////////////////////////////////////////////////////////
//these functions are overloaded, they go in conjunction with those in obserer.h that are virtual variables.
//the increase of the variable is a subject, here what it does is to make update of that amount to the variable that is in player.
    void Player::collisionCounter(int collision){
        collisionCount = collision;
    }
    void Player::itemCounter(int item){
        itemCount = item;
    }
    void Player::healthCounter(int health){
        healthCount = health;
    }
//////////////////////////////////////////////////////////////////////////////////////


    void Player::resolvePlatformCollision(const Platform& platform) {
        //si player choca con una plataforma se activa if
        if (getBounds().intersects(platform.getBounds())) {
            sf::FloatRect playerBounds = getBounds();
            sf::FloatRect platformBounds = platform.getBounds();
            sf::Vector2f pos = sprite.getPosition();

            if (playerBounds.top + playerBounds.height -20 < platformBounds.top) {  //to "step on" the platform
                sprite.setPosition(pos.x, platformBounds.top - playerBounds.height);
                velocity.y = 0;
                isJumping = false;
            }
            else if (playerBounds.top < platformBounds.top + platformBounds.height && //to hit a platform from below
                playerBounds.top > platformBounds.top &&
                velocity.y < 0) {
                sprite.setPosition(pos.x, platformBounds.top + platformBounds.height); 
                velocity.y = 0;
            }
            else if (playerBounds.left + playerBounds.width > platformBounds.left && //to crash sideways
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
            // If there is no collision, allow the player to fall if he is in the air.
            if (!isJumping && velocity.y == 0) {
                velocity.y = 300.0f;  
            }
        }
    }

    void Player::resolveCollision(Player& other) {
        // if the player collides with another player it is activated.
        if (getBounds().intersects(other.getBounds())) {
            sf::FloatRect thisBounds = getBounds();
            sf::FloatRect otherBounds = other.getBounds();
            sf::Vector2f thisPos = sprite.getPosition();
            sf::Vector2f otherPos = other.sprite.getPosition();
            //variables to check if there is collision from above specifically
            bool isLandingOnTop = thisBounds.top + thisBounds.height - 5.0f <= otherBounds.top;
            bool isOtherOnTop = otherBounds.top + otherBounds.height - 5.0f <= thisBounds.top;

            //vertical collision

            if (velocity.y > 0 && isLandingOnTop) {
                sprite.setPosition(thisPos.x, otherBounds.top - thisBounds.height);
                velocity.y = 0;
                isJumping = false;
            }else if (velocity.y < 0 && isOtherOnTop) {
                other.sprite.setPosition(otherPos.x, thisBounds.top - otherBounds.height);
                other.velocity.y = 0;
                other.isJumping = false;
            }
            //horizontal collision

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

//return fireballs
    std::vector<Fireball>& Player::getFireballs() {
        return fireballs;
    }
//specific check to see if player is colliding with another object
    bool Player::isColliding(const sf::FloatRect& other) {
        return sprite.getGlobalBounds().intersects(other);
    }
