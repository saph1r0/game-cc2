#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "ItemFactory.h"
#include "Item.h"
#include "Player.h"
#include "Subject.h"
#include "Platform.hpp"
#include "Level.hpp" //esta añadiendo level.hpp

/*
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
*/

void handleCollisions(Player& player1, Player& player2, const std::vector<Platform*>& platforms);

enum GameState {
    INTRO,
    MENU,
    PLAYING,
    WIN
};


int main() {

    std::string player1Name, player2Name;

    std::cout << "Nombre de Jugador 1: ";
    std::getline(std::cin, player1Name); 

    std::cout << "Nombre de Jugador 2: ";
    std::getline(std::cin, player2Name);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;

    int mapOffsetX = (SCREEN_WIDTH - 56 * 32) / 2;
    int mapOffsetY = (SCREEN_HEIGHT - 15 * 32) / 2;

    Level level(mapOffsetX, mapOffsetY, SCREEN_WIDTH, SCREEN_HEIGHT); ////////////////OBJECTO LEVEL

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

    sf::Texture itemTexture;
    if (!itemTexture.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/spritesheet.png")) {
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/Retro Gaming.ttf")) {
        return -1;
    }

    sf::Texture fireballTexture;
    if (!fireballTexture.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/Fireball Spritesheet.png")) {
        return -1;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Text introText("Press Enter to Play", font, 50);
    introText.setFillColor(sf::Color::White);
    introText.setPosition((SCREEN_WIDTH - introText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - introText.getLocalBounds().height) / 2);

    sf::Text winText("El ganador es: ", font, 25);
    winText.setFillColor(sf::Color::White);
    winText.setPosition((SCREEN_WIDTH - winText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - winText.getLocalBounds().height) / 2);

    sf::Text menuText("Select Level:\n1. Level 1\n2. Level 2\n3. Level 3\n4. Level 4\n5. Level 5\n6. Level 6\n7. Level 7\n8. Level 8\n9. Level 9\n10. Level 10", font, 30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition((SCREEN_WIDTH - menuText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - menuText.getLocalBounds().height) / 2);

    GameState gameState = INTRO;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Player> players;
    
    Player player1("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 0.0f), 1 ,player1Name, font);
    Player player2("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2 ,player2Name, font);
    players.push_back(player1);
    players.push_back(player2);

    const int itemWidth = 64;  // ancho
    const int itemHeight = 64; // altura
    const int numItems = 8;   // número de ítems
    const float itemScale = 0.5f;

    std::vector<Item> items;
    //createItems(itemTexture, items, itemWidth, itemHeight, numItems, window.getSize(), platforms, itemScale);
    ItemFactory::createItems(itemTexture, items, itemWidth, itemHeight, numItems, level.getPlatforms(), itemScale);


    sf::Clock clock;

    ////////////////////////////////OBSERVER///////////////////////////////////////////////////
        Subject gameSubject1;
        Subject gameSubject2;

        gameSubject1.addObserver(&player1);
        gameSubject2.addObserver(&player2);

        gameSubject1.setItem(0);
        gameSubject1.setCollision(0);

        gameSubject2.setItem(0);
        gameSubject2.setCollision(0);

    ////////////////////////////////////////////////////////////////////////////////////
    sf::Text text;
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
    sf::Text text2;
            text2.setFont(font);
            text2.setCharacterSize(20);
            text2.setFillColor(sf::Color::White);
    ////////////////////////////////////////////////////////////////////////////////////
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
                        std::cout<<levelIndex<<std::endl;
                        if (levelIndex >= 0 && levelIndex < 10) {
                            level.loadLevel(mapOffsetX, mapOffsetY, levelIndex);
                            gameState = PLAYING;
                        }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        std::string winnerName;
        if(gameState == PLAYING){
            player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::F, &fireballTexture);
            player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Space, &fireballTexture);

            player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
            player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);

            

            if (level.checkLevelTransition(player1.getBounds()) || level.checkLevelTransition(player2.getBounds())) {
                int temporal = level.getLevel();
                items.clear();
                players.clear();
                if(temporal == 9){
                    winnerName = (gameSubject1.getItem() > gameSubject2.getItem()) ? player1Name : player2Name; 
                    winText.setString("El ganador es: " + winnerName);
                    gameState =WIN;
                }else{
                    level.loadLevel(mapOffsetX, mapOffsetY,temporal); ///here
                    ItemFactory::createItems(itemTexture, items, itemWidth, itemHeight, numItems, level.getPlatforms(), itemScale);
                    Player player1("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 0.0f), 1 ,player1Name, font);
                    Player player2("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2 ,player2Name, font);

                }
            }

            level.updateTransition(deltaTime);

            handleCollisions(player1, player2, level.getPlatforms());

            // Verificar colisiones de las bolas de fuego
            for (auto& fireball : player1.getFireballs()) {
                if (fireball.isColliding(player2.getBounds())) {
                    gameSubject2.addCollision();
                    fireball.setToBeDestroyed(true);
                }
            }

            for (auto& fireball : player2.getFireballs()) {
                if (fireball.isColliding(player1.getBounds())) {
                    gameSubject1.addCollision();
                    fireball.setToBeDestroyed(true);
                }
            }

            for (auto it = items.begin(); it != items.end();) {
                if (player1.isColliding(it->getBounds())) {
                    gameSubject1.addItem();
                    it = items.erase(it);
                } else {
                    ++it;
                }
            }

            for (auto it = items.begin(); it != items.end();) {
                if (player2.isColliding(it->getBounds())) {
                    gameSubject2.addItem();
                    it = items.erase(it);
                } else {
                    ++it;
                }
            }

            

            std::stringstream ss;
            ss << player1Name << " Collisions: " << gameSubject1.getCollision() << "\n";
            ss << player1Name << " Items: " << gameSubject1.getItem() << "\n";

            std::stringstream sss;
            sss << player2Name << " Collisions: " << gameSubject2.getCollision() << "\n";
            sss << player2Name << " Items: " << gameSubject2.getItem() << "\n";

            text.setString(ss.str());
            text.setPosition(10, 10);
            
            text2.setString(sss.str());
            text2.setPosition(800, 10);

            

        }
        

        window.clear(sf::Color::Black);

        if (gameState == INTRO) {
            window.draw(introText);
        } else if (gameState == MENU) {
            window.draw(menuText);
        } else if (gameState == PLAYING) {
            level.draw(window);
            if(!level.getTransition()){
                player1.draw(window);
                player2.draw(window);
                // Dibujar ítems
                for (auto& item : items) {
                    item.draw(window);
                }
                window.draw(text);
                window.draw(text2);
            }
            
        } else if(gameState == WIN){
            window.draw(winText);
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