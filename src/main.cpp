#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Platform.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "El Juego");
    sf::Font font;
    font.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Retro Gaming.ttf");

    sf::Texture playerTextureRight;
    sf::Texture playerTextureLeft;
    sf::Texture fireballTexture;
    sf::Texture backgroundTexture;

    backgroundTexture.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Space Background.png");
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    playerTextureRight.loadFromFile("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png");
    playerTextureLeft.loadFromFile("//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png");
    fireballTexture.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Fireball Spritesheet.png");

    Player player1("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png", "//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 400.0f), 1);
    Player player2("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png", "//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2);

    std::vector<Platform> platforms;
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(300.0f, 400.0f)));
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(0.0f, 500.0f)));
    platforms.push_back(Platform(sf::Vector2f(300.0f, 20.0f), sf::Vector2f(500.0f, 300.0f)));
    platforms.push_back(Platform(sf::Vector2f(100.0f, 20.0f), sf::Vector2f(100.0f, 100.0f) ));

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
        player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::F, &fireballTexture);
        player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Space, &fireballTexture);

        player1.update(deltaTime);
        player2.update(deltaTime);

        for (auto& platform : platforms) {
            player1.resolvePlatformCollision(platform);
            player2.resolvePlatformCollision(platform);
        }
        player1.resolveCollision(player2);
        player2.resolveCollision(player1);

        // Check for fireball collisions
        for (auto& fireball : player1.getFireballs()) {
            if (fireball.isColliding(player2.getBounds())) {
                player2.increaseCollisionCount();
                fireball.setToBeDestroyed(true);
            }
        }

        for (auto& fireball : player2.getFireballs()) {
            if (fireball.isColliding(player1.getBounds())) {
                player1.increaseCollisionCount();
                fireball.setToBeDestroyed(true);
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        for (auto& platform : platforms) {
            platform.draw(window);
        }
        player1.draw(window);
        player2.draw(window);

        // Draw collision counts and velocities
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        std::stringstream ss;
        ss << "Player 1 Collisions: " << player1.getCollisionCount() << "\n";
        ss << "Player 1 Velocity: (" << player1.getVelocity().x << ", " << player1.getVelocity().y << ")\n";
        ss << "Player 2 Collisions: " << player2.getCollisionCount() << "\n";
        ss << "Player 2 Velocity: (" << player2.getVelocity().x << ", " << player2.getVelocity().y << ")";
        text.setString(ss.str());
        text.setPosition(10, 10);

        window.draw(text);
        window.display();
    }

    return 0;
}
