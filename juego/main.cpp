#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Platform.hpp"
#include "Level.hpp"
#include <iostream>
#include <vector>
#include <sstream>

extern const float GRAVITY = 980.0f;
extern const float JUMP_SPEED = -450.0f;
extern const float MOVE_SPEED = 200.0f;

void handleCollisions(Player& player1, Player& player2, const std::vector<Platform*>& platforms);

enum GameState {
    INTRO,
    MENU,
    PLAYING
};

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;

    int mapOffsetX = (SCREEN_WIDTH - 56 * 32) / 2;
    int mapOffsetY = (SCREEN_HEIGHT - 15 * 32) / 2;

    Level level(mapOffsetX, mapOffsetY, SCREEN_WIDTH, SCREEN_HEIGHT);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

    sf::Font font;
    if (!font.loadFromFile("/home/diogo/Documentos/juego/imagenes/arial.ttf")) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text introText("Press Enter to Play", font, 50);
    introText.setFillColor(sf::Color::White);
    introText.setPosition((SCREEN_WIDTH - introText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - introText.getLocalBounds().height) / 2);

    sf::Text menuText("Select Level:\n1. Level 1\n2. Level 2\n3. Level 3\n4. Level 4\n5. Level 5\n6. Level 6\n7. Level 7\n8. Level 8\n9. Level 9\n10. Level 10", font, 30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition((SCREEN_WIDTH - menuText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - menuText.getLocalBounds().height) / 2);

    GameState gameState = INTRO;

    sf::Texture player1RightTexture;
    player1RightTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/AnimationSheetderecha.png");

    sf::Texture player1LeftTexture;
    player1LeftTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/AnimationSheetizq.png");

    sf::Texture player2RightTexture;
    player2RightTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/AnimationSheetderecha.png");

    sf::Texture player2LeftTexture;
    player2LeftTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/AnimationSheetizq.png");

    sf::Texture fireballTexture;
    fireballTexture.loadFromFile("/home/diogo/Documentos/juego/imagenes/fire.png");

    Player player1("/home/diogo/Documentos/juego/imagenes/AnimationSheetderecha.png", "/home/diogo/Documentos/juego/imagenes/AnimationSheetizq.png", sf::Vector2f(100.0f, 100.0f), 1);
    Player player2("/home/diogo/Documentos/juego/imagenes/AnimationSheetderecha.png", "/home/diogo/Documentos/juego/imagenes/AnimationSheetizq.png", sf::Vector2f(500.0f, 100.0f), 2);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (gameState == INTRO && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameState = MENU;
            }

            if (gameState == MENU && event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                        int levelIndex = event.key.code - sf::Keyboard::Num1;
                        if (levelIndex >= 0 && levelIndex < 10) {
                            level.loadLevel(mapOffsetX, mapOffsetY, levelIndex);
                            gameState = PLAYING;
                        }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (gameState == PLAYING) {
            player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space, &fireballTexture);
            player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::RControl, &fireballTexture);

            player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
            player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);

            handleCollisions(player1, player2, level.getPlatforms());

            if (level.checkLevelTransition(player1.getBounds()) || level.checkLevelTransition(player2.getBounds())) {
                level.loadLevel(mapOffsetX, mapOffsetY);
            }

            level.updateTransition(deltaTime);
        }

        window.clear(sf::Color::Black);

        if (gameState == INTRO) {
            window.draw(introText);
        } else if (gameState == MENU) {
            window.draw(menuText);
        } else if (gameState == PLAYING) {
            level.draw(window);
            player1.draw(window);
            player2.draw(window);
        }

        window.display();
    }

    return 0;
}
void handleCollisions(Player& player1, Player& player2, const std::vector<Platform*>& platforms) {
    player1.resolveCollision(player2);
    player2.resolveCollision(player1);

    for (auto& platform : platforms) {
        player1.resolvePlatformCollision(*platform);
        player2.resolvePlatformCollision(*platform);
    }
}
