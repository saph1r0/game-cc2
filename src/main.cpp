#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Platform.h"
#include "Coin.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "El Juego");
    sf::Font font;
    font.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/Retro Gaming.ttf");

    // Cargar texturas
    sf::Texture playerTextureRight;
    sf::Texture playerTextureLeft;
    sf::Texture fireballTexture;
    sf::Texture backgroundTexture;
    sf::Texture coinTexture; // Agregado para la textura de la moneda

    // Cargar texturas adicionales
    backgroundTexture.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/Space Background.png");
    playerTextureRight.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/AnimationSheetderecha.png");
    playerTextureLeft.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/AnimationSheetizq.png");
    fireballTexture.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/Fireball Spritesheet.png");
    coinTexture.loadFromFile("/Users/HP/Documents/Carrera/Segundo Año/Ciencias de la Computación 2/Videojuego2/images/green_coin.png"); // Agregado para la textura de la moneda

    // Crear jugadores
    Player player1(playerTextureRight, playerTextureLeft, sf::Vector2f(100.0f, 400.0f), 1);
    Player player2(playerTextureRight, playerTextureLeft, sf::Vector2f(600.0f, 400.0f), 2);

    // Crear plataformas
    std::vector<Platform> platforms;
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(300.0f, 400.0f)));
    platforms.push_back(Platform(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(0.0f, 500.0f)));
    platforms.push_back(Platform(sf::Vector2f(300.0f, 20.0f), sf::Vector2f(500.0f, 300.0f)));
    platforms.push_back(Platform(sf::Vector2f(100.0f, 20.0f), sf::Vector2f(100.0f, 100.0f)));

    // Crear vector de monedas
    std::vector<Coin> coins;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Manejar la entrada de los jugadores
        player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::F, &fireballTexture);
        player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Space, &fireballTexture);

        // Actualizar jugadores
        player1.update(deltaTime);
        player2.update(deltaTime);

        // Resolver colisiones con plataformas
        for (auto& platform : platforms) {
            player1.resolvePlatformCollision(platform);
            player2.resolvePlatformCollision(platform);
        }

        // Resolver colisión entre jugadores
        player1.resolveCollision(player2);
        player2.resolveCollision(player1);

        // Generación de monedas aleatoriamente
        if (rand() % 100 == 0) { // Genera una moneda con probabilidad baja
            coins.push_back(Coin({coinTexture}, platforms)); // Se pasa el vector de texturas como un vector de una sola textura
        }

        // Actualización y dibujo de las monedas
        for (auto it = coins.begin(); it != coins.end();) {
            it->update(deltaTime);
            it->draw(window);

            // Verificar colisión con jugadores
            if (player1.getBounds().intersects(it->getBounds()) && !it->isCollected()) {
                player1.increaseScore();
                it->setCollected(true);
            }
            if (player2.getBounds().intersects(it->getBounds()) && !it->isCollected()) {
                player2.increaseScore();
                it->setCollected(true);
            }

            // Eliminar la moneda si ya fue recolectada
            if (it->isCollected()) {
                it = coins.erase(it);
            } else {
                ++it;
            }
        }

        // Renderizado del juego
        window.clear();
        window.draw(backgroundSprite);
        for (auto& platform : platforms) {
            platform.draw(window);
        }
        player1.draw(window);
        player2.draw(window);
        for (auto& coin : coins) {
            coin.draw(window);
        }
        window.display();
    }

    return 0;
}
