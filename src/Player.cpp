#include "Player.h"

const float GRAVITY = 980.0f;
const float JUMP_SPEED = -450.0f;
const float MOVE_SPEED = 200.0f;

Player::Player(const sf::Texture& textureRight, const sf::Texture& textureLeft, sf::Vector2f position, int number)
    : velocity(0.0f, 0.0f), state(PlayerState::Idle), onGround(false), playerNum(number), score(0), collisionCount(0)
{
    spriteRight.setTexture(textureRight);
    spriteLeft.setTexture(textureLeft);
    sprite = spriteRight; // Iniciar con la textura derecha
    sprite.setPosition(position);
    sprite.setScale(3.0f, 4.0f);

    for (int i = 0; i < 4; ++i) {
        int x = 96 + i * 24;
        runningFrames.push_back(sf::IntRect(x + 6, 30, 14, 18));
    }
    for (int i = 0; i < 8; ++i) {
        int x = 0 + i * 24;
        jumpingFrames.push_back(sf::IntRect(x + 6, 78, 14, 18));
    }
    sprite.setTextureRect(runningFrames[currentFrame]);
}

void Player::update(float deltaTime) {
    if (!onGround) {
        velocity.y += GRAVITY * deltaTime;
    }

    sprite.move(velocity * deltaTime);

    sf::Vector2f pos = sprite.getPosition();

    if (pos.y + sprite.getGlobalBounds().height >= 600.0f) {
        sprite.setPosition(pos.x, 600.0f - sprite.getGlobalBounds().height);
        velocity.y = 0;
        onGround = true;
    }

    if (pos.x < 0) {
        sprite.setPosition(0, pos.y);
    } else if (pos.x + sprite.getGlobalBounds().width >= 800) {
        sprite.setPosition(800 - sprite.getGlobalBounds().width, pos.y);
    }

    if (velocity.x != 0) {
        timeSinceLastFrame += deltaTime;
        if (timeSinceLastFrame >= frameTime) {
            currentFrame = (currentFrame + 1) % runningFrames.size();
            sprite.setTextureRect(runningFrames[currentFrame]);
            timeSinceLastFrame = 0.0f;
        }
    }

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

void Player::handleInput(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, sf::Keyboard::Key attackKey, sf::Texture* fireballTexture) {
    if (sf::Keyboard::isKeyPressed(leftKey)) {
        velocity.x = -MOVE_SPEED;
        sprite = spriteLeft;
    } else if (sf::Keyboard::isKeyPressed(rightKey)) {
        velocity.x = MOVE_SPEED;
        sprite = spriteRight;
    } else {
        velocity.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(jumpKey) && onGround) {
        velocity.y = JUMP_SPEED;
        onGround = false;
        state = PlayerState::Jumping;
        sprite.setTextureRect(jumpingFrames[currentFrame]);
    }

    if (sf::Keyboard::isKeyPressed(attackKey)) {
        sf::Vector2f fireballDirection;
        if (sprite == spriteRight) {
            fireballDirection = sf::Vector2f(1.0f, 0.0f);
        } else {
            fireballDirection = sf::Vector2f(-1.0f, 0.0f);
        }
        shoot(fireballTexture, fireballDirection);
    }
}

void Player::resolvePlatformCollision(const Platform& platform) {
    if (sprite.getGlobalBounds().intersects(platform.getBounds())) {
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::FloatRect platformBounds = platform.getBounds();
        sf::Vector2f pos = sprite.getPosition();

        if (playerBounds.top + playerBounds.height - 5 < platformBounds.top) {
            sprite.setPosition(pos.x, platformBounds.top - playerBounds.height);
            velocity.y = 0;
            onGround = true;
        } else if (playerBounds.top < platformBounds.top + platformBounds.height &&
                   playerBounds.top > platformBounds.top &&
                   velocity.y < 0) {
            sprite.setPosition(pos.x, platformBounds.top + platformBounds.height);
            velocity.y = 0;
        } else if (playerBounds.left + playerBounds.width > platformBounds.left &&
                   playerBounds.left < platformBounds.left + platformBounds.width &&
                   playerBounds.top + playerBounds.height > platformBounds.top) {
            if (velocity.x > 0) {
                sprite.setPosition(platformBounds.left - playerBounds.width, pos.y);
            } else if (velocity.x < 0) {
                sprite.setPosition(platformBounds.left + platformBounds.width, pos.y);
            }
            velocity.x = 0;
        }
    }
}

void Player::resolveCollision(Player& other) {
    if (sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds())) {
        sf::FloatRect thisBounds = sprite.getGlobalBounds();
        sf::FloatRect otherBounds = other.sprite.getGlobalBounds();
        sf::Vector2f thisPos = sprite.getPosition();
        sf::Vector2f otherPos = other.sprite.getPosition();

        bool isLandingOnTop = thisBounds.top + thisBounds.height - 5.0f <= otherBounds.top;
        bool isOtherOnTop = otherBounds.top + otherBounds.height - 5.0f <= thisBounds.top;

        if (velocity.y > 0 && isLandingOnTop) {
            sprite.setPosition(thisPos.x, otherBounds.top - thisBounds.height);
            velocity.y = 0;
            onGround = true;
        } else if (velocity.y < 0 && isOtherOnTop) {
            other.sprite.setPosition(otherPos.x, thisBounds.top - otherBounds.height);
            other.velocity.y = 0;
            other.onGround = true;
        }

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
    } else {
        // Allow player to fall if not jumping and in the air
        if (onGround && velocity.y == 0) {
            velocity.y = GRAVITY * 0.1f; // Pequeño impulso hacia abajo para evitar "pegarse" a las plataformas
            onGround = false;
        }
    }
}

void Player::shoot(sf::Texture* fireballTexture, sf::Vector2f direction) {
    int startPower = 10;
    if (fireballs.size() < 3) { // Limitar a 3 fireballs en pantalla
        sf::IntRect fireballRect;
        if (direction.x > 0) {
            fireballRect = sf::IntRect(0, 4 * fireballTexture->getSize().y / 8, fireballTexture->getSize().x / 8, fireballTexture->getSize().y / 8);
        } else {
            fireballRect = sf::IntRect(0, 0, fireballTexture->getSize().x / 8, fireballTexture->getSize().y / 8);
        }
        fireballs.emplace_back(fireballTexture, fireballRect, playerNum, sprite.getPosition(), direction, startPower);
    }
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::increaseScore() {
    score++;
}

int Player::getScore() const {
    return score;
}

std::vector<Fireball>& Player::getFireballs() {
    return fireballs;
}

int Player::getCollisionCount() const {
    return collisionCount;
}

void Player::increaseCollisionCount() {
    collisionCount++;
}

sf::Vector2f Player::getVelocity() const {
    return velocity;
}
