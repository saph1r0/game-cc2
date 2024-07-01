#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Item.h"
#include "Player.h"
#include "Platform.h"

void createItems(const sf::Texture& texture, std::vector<Item>& items, int itemWidth, int itemHeight, int numItems, const sf::Vector2u& windowSize) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Inicializa la semilla para los números aleatorios

    for (int i = 0; i < numItems; ++i) {
        int x = (i * itemWidth) % texture.getSize().x;
        int y = ((i * itemWidth) / texture.getSize().x) * itemHeight;

        sf::IntRect rect(x, y, itemWidth, itemHeight);

        // Generar una posición aleatoria dentro del tamaño de la ventana
        float posX = static_cast<float>(std::rand() % (windowSize.x - itemWidth));
        float posY = static_cast<float>(std::rand() % (windowSize.y - itemHeight));

        items.emplace_back(texture, rect, sf::Vector2f(posX, posY));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "El Juego");
    sf::Texture itemTexture;
    if (!itemTexture.loadFromFile("//home/ubuntu20/Documentos/spritesheet.png")) {
        return -1;
    }
    sf::Font font;
    if (!font.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Retro Gaming.ttf")) {
        return -1;
    }

    sf::Texture playerTextureRight;
    sf::Texture playerTextureLeft;
    sf::Texture fireballTexture;
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Space Background.png") ||
        !playerTextureRight.loadFromFile("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png") ||
        !playerTextureLeft.loadFromFile("//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png") ||
        !fireballTexture.loadFromFile("//home/ubuntu20/c++/game-cc2/images/Fireball Spritesheet.png")) {
        return -1;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    Player player1("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png", "//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 400.0f), 1);
    Player player2("//home/ubuntu20/c++/game-cc2/images/AnimationSheetderecha.png", "//home/ubuntu20/c++/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2);

    std::vector<Platform> platforms;
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(300.0f, 400.0f)));
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(0.0f, 500.0f)));
    platforms.push_back(Platform(sf::Vector2f(300.0f, 20.0f), sf::Vector2f(500.0f, 300.0f)));
    platforms.push_back(Platform(sf::Vector2f(100.0f, 20.0f), sf::Vector2f(100.0f, 100.0f)));

    const int itemWidth = 16;  // Ancho de cada ítem en el sprite sheet
    const int itemHeight = 16; // Alto de cada ítem en el sprite sheet
    const int numItems = 10;   // Número de ítems a dispersar

    std::vector<Item> items;
    createItems(itemTexture, items, itemWidth, itemHeight, numItems, window.getSize());

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

        for (const auto& item : items) {
            item.draw(window);
        }

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

 

