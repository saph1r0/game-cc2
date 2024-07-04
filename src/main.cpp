#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Platform.h"



int main() {
    sf::Font font;
    font.loadFromFile("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/Retro Gaming.ttf");

    sf::Texture playerTextureRight;
    sf::Texture playerTextureLeft;
    sf::Texture fireballTexture;
    
    playerTextureRight.loadFromFile("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetderecha.png");
    playerTextureLeft.loadFromFile("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetizq.png");
    fireballTexture.loadFromFile("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/Fireball Spritesheet.png");

    Player player1("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetderecha.png", "/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 400.0f), 1);
    Player player2("/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetderecha.png", "/Users/Kathy/Documents/1. UNSA/2. AULA VIRTUAL/1. Ciencia de la Computacion II/JUEGO_UPDATE/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;
    const int TILE_SIZE = 32; // Tamaño de las plataformas en píxeles

    // Definición del nivel como cadena de caracteres
    const std::string level =
        "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^"
        "^......................................................^"
        "^......................................................^"
        "^......................................................^"
        "^......................................................^"
        "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
        "^......................................................^"
        "^......................................................^"
        "^..........................................^...........^"      
        "^......................................................^"
        "^.....^..^^^^..^...............^.....^..^....^.........^"
        "^......................................................^"
        "^......................................................^"
        "^........................-.............................^"
        "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";

    const int LEVEL_WIDTH = 56; // Ancho del nivel en número de baldosas
    const int LEVEL_HEIGHT = 15; // Alto del nivel en número de baldosas

    const int LEVEL_PIXEL_WIDTH = LEVEL_WIDTH * TILE_SIZE;
    const int LEVEL_PIXEL_HEIGHT = LEVEL_HEIGHT * TILE_SIZE;

    int mapOffsetX = (SCREEN_WIDTH - LEVEL_PIXEL_WIDTH) / 2;
    int mapOffsetY = (SCREEN_HEIGHT - LEVEL_PIXEL_HEIGHT) / 2;

    // Crear plataformas según el nivel definido
    std::vector<Platform> platforms;
    for (int y = 0; y < LEVEL_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH; ++x) {
            char tile = level[y * LEVEL_WIDTH + x];
            if (tile != '.') {
                sf::Vector2f position(x * TILE_SIZE + mapOffsetX, y * TILE_SIZE + mapOffsetY);
                platforms.push_back(Platform(sf::Vector2f(TILE_SIZE, TILE_SIZE), position));
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");


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

        player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);

        std::vector<Player> players;

        players.push_back(player1);
        players.push_back(player2);


        player1.resolveCollision(player2);
        player2.resolveCollision(player1);

        for (auto& platform : platforms) {
            player1.resolvePlatformCollision(platform);
            player2.resolvePlatformCollision(platform);
        }

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
