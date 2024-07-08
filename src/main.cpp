#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include "Item.h"
#include "Player.h"
#include "Platform.h"
//#include "CollisionManager.h"

void createItems(const sf::Texture& texture, std::vector<Item>& items, int itemWidth, int itemHeight, int numItems, const sf::Vector2u& windowSize, const std::vector<Platform>& platforms, float scale) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 

    for (int i = 0; i < numItems; ++i) {
        int x = (i * itemWidth) % texture.getSize().x;
        int y = ((i * itemWidth) / texture.getSize().x) * itemHeight;

        sf::IntRect rect(x, y, itemWidth, itemHeight);
        const Platform& platform = platforms[std::rand() % platforms.size()];
        sf::FloatRect bounds = platform.getBounds();

        float posX = bounds.left + static_cast<float>(std::rand() % static_cast<int>(bounds.width - itemWidth));
        float posY = bounds.top - itemHeight; // Arriba de la plataforma

        items.emplace_back(texture, rect, sf::Vector2f(posX, posY), scale); // Pasa el factor de escala aquí
    }
}

int main() {
    std::string player1Name, player2Name;

    std::cout << "Nombre de Jugador 1: ";
    std::getline(std::cin, player1Name); // Cambiar std::cin >> Player1 por std::getline para permitir espacios

    std::cout << "Nombre de Jugador 2: ";
    std::getline(std::cin, player2Name); // Cambiar std::cin >> Player2 por std::getline para permitir espacios


    sf::Texture itemTexture;
    if (!itemTexture.loadFromFile("/directorio/game-cc2/images/spritesheet.png")) {
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("/directorio/game-cc2/images/Retro Gaming.ttf")) {
        return -1;
    }

    sf::Texture fireballTexture;
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("/directorio/game-cc2/images/Space Background.png") ||
        !fireballTexture.loadFromFile("/directorio/game-cc2/images/Fireball Spritesheet.png")) {
        return -1;
    }

    Player player1("/directorio/game-cc2/images/AnimationSheetderecha.png", "/directorio/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 0.0f), 1);
    Player player2("/directorio/game-cc2/images/AnimationSheetderecha.png", "/directorio/game-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2);


    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;
    const int TILE_SIZE = 32; // Tamaño de las plataformas en píxeles

    // Definición del nivel como cadena de caracteres
    const std::string level =
        "..................................................."
        "^.................................................^"
        "^.........^^^......^^^^^^^^^^^^^^^^^^.............^"
        "^.................................................^"
        "^...^^^...................................^^^^^^^.^"
        "^.................................................^"
        "^..........^^^....................^^^^^^^^^^^^....^"
        "^.................................................^"
        "^................^^^^^^^^^^^^.....................^"      
        "^.................................................^"
        "^^^^^^^^^^^^^.....................................^"
        "^.................................................^"
        "^..............^^^^^^^^^^^^.......................^"
        "^...............................^^^^^^^^^^^^^^^^^^^"
        "..................................................."
        "..................................................."
        ".........................^^^^......................";

    const int LEVEL_WIDTH = 51; // Ancho del nivel en número de baldosas
    const int LEVEL_HEIGHT = 17; // Alto del nivel en número de baldosas

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
                sf::Vector2f position(x * TILE_SIZE + mapOffsetX , y * TILE_SIZE + mapOffsetY);
                platforms.push_back(Platform(sf::Vector2f(TILE_SIZE, TILE_SIZE), position));
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

    const int itemWidth = 64;  // ancho
    const int itemHeight = 64; // altura
    const int numItems = 8;   // número de ítems
    const float itemScale = 0.5f;

    std::vector<Item> items;
    createItems(itemTexture, items, itemWidth, itemHeight, numItems, window.getSize(), platforms, itemScale);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        //std::cout<<deltaTime<<std::endl;

        player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::F, &fireballTexture);
        player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Space, &fireballTexture);

        player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);



        for (auto& platform : platforms) {
            player1.resolvePlatformCollision(platform);
            player2.resolvePlatformCollision(platform);
        }

        player1.resolveCollision(player2);
        player2.resolveCollision(player1);

        // Verificar colisiones de las bolas de fuego
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
        

        // Verificar colisiones con ítems y recolectarlos
        for (auto it = items.begin(); it != items.end();) {
            if (player1.isColliding(it->getBounds())) {
                player1.collectItem();
                it = items.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = items.begin(); it != items.end();) {
            if (player2.isColliding(it->getBounds())) {
                player2.collectItem();
                it = items.erase(it);
            } else {
                ++it;
            }
        }

        // Dibujar ítems
        for (auto& item : items) {
            item.draw(window);
        }

        for (auto& platform : platforms) {
            platform.draw(window);
        }

        player1.draw(window);
        player2.draw(window);

        // Dibujar contadores de colisiones, velocidades e ítems recolectados
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        std::stringstream ss;
        ss << player1Name << " Collisions: " << player1.getCollisionCount() << "\n";
        ss << player1Name << " Items: " << player1.getItemCount() << "\n";
        ss << player1Name << " Collisions: " << player2.getCollisionCount() << "\n";
        ss << player2Name << " Items: " << player2.getItemCount() << "\n";

        text.setString(ss.str());
        text.setPosition(10, 10);
        window.draw(text);

        window.display();
    }

    return 0;
}
