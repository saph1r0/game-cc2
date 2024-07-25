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
#include "Strategy.hpp"
#include <thread>//theads
#include <mutex>
#include "Button.h"


void handleCollisions(Player& player1, Player& player2, const std::vector<Platform*>& platforms);
// Function to handle collisions between players and platforms.
enum GameState {
    INTRO,
    MENU,
    PLAYING,
    WIN
};/*Enum to track the state of the game. It can be in
 the introduction screen, menu, playing state, or win state*/


int main() {
    std::mutex mtx; /*object used to synchronize access to shared data between threads, ensuring 
     that only one thread can access the shared resource at a time.*/
    std::string player1Name, player2Name;

    //Reads player names from the console input.
    std::cout << "Nombre de Jugador 1: ";
    std::getline(std::cin, player1Name); 

    std::cout << "Nombre de Jugador 2: ";
    std::getline(std::cin, player2Name);

    /*Retrieves the current desktop screen resolution.*/
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int SCREEN_WIDTH = desktop.width - 95;
    int SCREEN_HEIGHT = desktop.height - 95;

    int mapOffsetX = (SCREEN_WIDTH/32 ) / 2;
    int mapOffsetY = (SCREEN_HEIGHT/2 ) / 2;

    std::cout<<"h: "<<SCREEN_HEIGHT<<std::endl;
    std::cout<<"w: "<<SCREEN_WIDTH<<std::endl;

    Level level(mapOffsetX, mapOffsetY, SCREEN_WIDTH, SCREEN_HEIGHT); ////////////////OBJECTO LEVEL
    // Creates a window for rendering the game.
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

    //Loads textures for items and fireballs.
    sf::Texture itemTexture;
    if (!itemTexture.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/spritesheet.png")) {
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/Retro Gaming.ttf")) {
        return -1;
    }

    sf::Texture fireballTexture;
    if (!fireballTexture.loadFromFile("images/Fireball Spritesheet.png")) {
        return -1;
    }

    sf::Texture introBackgroundTexture;
    if (!introBackgroundTexture.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/fondos/intro.jpg")) {
        return -1; // Manejo de error si no se puede cargar la textura
    }

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("/home/ubuntu20/c++/gaamee-cc2/images/fondos/menu.jpg")) {
        return -1; // Manejo de error si no se puede cargar la textura
    }

    sf::Sprite introBackground(introBackgroundTexture);
    introBackground.setScale(static_cast<float>(SCREEN_WIDTH) / introBackground.getLocalBounds().width, 
                         static_cast<float>(SCREEN_HEIGHT) / introBackground.getLocalBounds().height);

    sf::Sprite menuBackground(menuBackgroundTexture);
    menuBackground.setScale(static_cast<float>(SCREEN_WIDTH) / menuBackground.getLocalBounds().width, 
                        static_cast<float>(SCREEN_HEIGHT) / menuBackground.getLocalBounds().height);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // Sets up text elements for intro, win, and menu screens. Positions them in the center of the screen.
    sf::Text introText("Press Enter to Play", font, 50);
    introText.setFillColor(sf::Color::White);
    introText.setPosition((SCREEN_WIDTH - introText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - introText.getLocalBounds().height) / 2);

    sf::Text winText("El ganador es: ", font, 25);
    winText.setFillColor(sf::Color::White);
    winText.setPosition((SCREEN_WIDTH - winText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - winText.getLocalBounds().height) / 2);

    sf::Text menuText("Select Level:\n Level 1\n Level 2\nLevel 3\nLevel 4\nLevel 5\nLevel 6\nLevel 7\nLevel 8\nLevel 9", font, 30);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition((SCREEN_WIDTH - menuText.getLocalBounds().width) / 2, (SCREEN_HEIGHT - menuText.getLocalBounds().height) / 2);

    GameState gameState = INTRO;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Player> players;
    //Creates two player objects with initial positions and textures.
    Player player1("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(100.0f, 0.0f), 1 ,player1Name, font);
    Player player2("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2 ,player2Name, font);
    players.push_back(player1);
    players.push_back(player2);

    Context* context = new Context(new fireballCostados());//Manages the strategy pattern for fireball attacks.

    const int itemWidth = 64;  
    const int itemHeight = 64;
    const int numItems = 8;   
    const float itemScale = 0.5f;

    std::vector<Item> items;
    //createItems(itemTexture, items, itemWidth, itemHeight, numItems, window.getSize(), platforms, itemScale);
    ItemFactory::createItems(itemTexture, items, itemWidth, itemHeight, numItems, level.getPlatforms(), itemScale);
    //Uses the ItemFactory to create and configure items in the game world.

    sf::Clock clock;

    ////////////////////////////////OBSERVER///////////////////////////////////////////////////
    /*Manages observers that are notified of changes. In this case, gameSubject1 and gameSubject2 will 
    notify player1 and player2 respectively.*/
        Subject gameSubject1;
        Subject gameSubject2;
        //Subject enemyAtack;

        gameSubject1.addObserver(&player1);
        gameSubject2.addObserver(&player2);

        //enemyAtack.addObserver(&player1);
        //enemyAtack.addObserver(&player2);

        gameSubject1.setItem(0);
        gameSubject1.setCollision(0);
        gameSubject1.setHealth(10); //20vidas para mejor oportunidad de terminar juego

        gameSubject2.setItem(0);
        gameSubject2.setCollision(0);
        gameSubject2.setHealth(10);

        //enemyAtack.setItem(0);
        //enemyAtack.setCollision(0);

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
    //theads
    float deltaTime = 0.0f;

    // Creates separate threads for updating each player to allow concurrent updates.
    std::thread player1Thread([&]() {
        while (window.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Aproximadamente 60 FPS
            std::unique_lock<std::mutex> lock(mtx);//Locks the mutex to ensure safe access to shared data when updating the player.
            player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
    });

    std::thread player2Thread([&]() {
        while (window.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Aproximadamente 60 FPS
            std::unique_lock<std::mutex> lock(mtx);
            player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
    });

    std::thread enemyThread([&]() {
        while (window.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Aproximadamente 60 FPS
            std::unique_lock<std::mutex> lock(mtx);
            context->executeStrategy(&fireballTexture, deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
    });

    /////////////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (gameState == INTRO && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameState = MENU;//transition to the menu state.
            }

            if (gameState == MENU && event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                        int levelIndex = event.key.code - sf::Keyboard::Num1;// the level index
                        std::cout<<levelIndex<<std::endl;
                        if (levelIndex >= 0 && levelIndex < 10) {// levelIndex is in valid range
                            level.loadLevel(mapOffsetX, mapOffsetY, levelIndex);//loading
                            gameState = PLAYING;
                        }
                }
            }
            // En el estado MENU
            if (gameState == MENU) {
                window.draw(menuBackground);

                // Create and draw buttons for each level
                std::vector<Button> levelButtons;
                float buttonWidth = 200;
                float buttonHeight = 50;
                float buttonSpacing = 10;
                sf::Vector2f buttonPosition((SCREEN_WIDTH - buttonWidth) / 2, (SCREEN_HEIGHT - 10 * (buttonHeight + buttonSpacing)) / 2);

                // Crear botones para los niveles del 1 al 9
                for (int i = 0; i < 9; ++i) {
                    std::string buttonText = "Level " + std::to_string(i + 1);
                    Button button(buttonPosition, sf::Vector2f(buttonWidth, buttonHeight), buttonText, font);//create
                    levelButtons.push_back(button);//add

                    //update pos for next button
                    buttonPosition.y += buttonHeight + buttonSpacing;
                }

                // draw detect clik
                for (auto& button : levelButtons) {
                    button.draw(window);
                }

                // Detect clicks to select a level
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
                    for (int i = 0; i < levelButtons.size(); ++i) {
                        if (levelButtons[i].isClicked(clickPosition)) {
                            // Seleccionar nivel i+1
                            int levelIndex = i;
                            level.loadLevel(mapOffsetX, mapOffsetY, levelIndex);
                            gameState = PLAYING;
                            break;
                        }
                    }
                }
            }


        }

        float deltaTime = clock.restart().asSeconds();//Calculate time elapsed since the last frame

        std::string winnerName;
        if(gameState == PLAYING){
            if(gameSubject1.getHealth() == 0){// Determine the winner if gameSubject1 is dead
                winnerName = (gameSubject1.getItem() > gameSubject2.getItem()) ? player1Name : player2Name; 
                winText.setString("GAME OVER\n"+player1Name+" murio.\n"+"Pero quien recolecto mas monedas fue " + winnerName);
                gameState = WIN;
            }
            if(gameSubject2.getHealth() == 0){
                winnerName = (gameSubject1.getItem() > gameSubject2.getItem()) ? player1Name : player2Name; 
                winText.setString("GAME OVER\n"+player2Name+" murio.\n"+"Pero quien recolecto mas monedas fue " + winnerName);
                gameState = WIN;
            }
            player1.handleInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::F, &fireballTexture);
            player2.handleInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Space, &fireballTexture);

            player1.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);
            player2.update(deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);

            context->executeStrategy(&fireballTexture, deltaTime, SCREEN_HEIGHT, SCREEN_WIDTH);

            
            // Check level transitions
            if (level.checkLevelTransition(player1.getBounds()) || level.checkLevelTransition(player2.getBounds())) {
                int temporal = level.getLevel(); // Get current level
                items.clear();
                players.clear();
                if(temporal == 9){// Handle end of final level
                    winnerName = (gameSubject1.getItem() > gameSubject2.getItem()) ? player1Name : player2Name; 
                    winText.setString("El ganador es: " + winnerName);
                    gameState =WIN;
                }else{//....next lv
                    level.loadLevel(mapOffsetX, mapOffsetY,temporal); 
                    ItemFactory::createItems(itemTexture, items, itemWidth, itemHeight, numItems, level.getPlatforms(), itemScale);
                    Player player1("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png",sf::Vector2f(100.0f, 0.0f), 1 ,player1Name, font);
                    Player player2("/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetderecha.png", "/home/ubuntu20/c++/gaamee-cc2/images/AnimationSheetizq.png", sf::Vector2f(600.0f, 400.0f), 2 ,player2Name, font);

                }
            }

            level.updateTransition(deltaTime);

            handleCollisions(player1, player2, level.getPlatforms());

            //Check fireball collisions
            for (auto& fireball : player1.getFireballs()) {
                for (auto& fireballE : context->getFireballs()) {
                    if(fireballE.isColliding(fireball.getBounds())){
                        fireball.setToBeDestroyed(true);
                        fireballE.setToBeDestroyed(true);
                    }
                }
                if (fireball.isColliding(player2.getBounds())) {
                    gameSubject2.removeHealth();
                    fireball.setToBeDestroyed(true);
                }
                
            }

            for (auto& fireball : player2.getFireballs()) {
                for (auto& fireballE : context->getFireballs()) {
                    if(fireballE.isColliding(fireball.getBounds())){
                        fireball.setToBeDestroyed(true);
                        fireballE.setToBeDestroyed(true);
                    }
                }
                if (fireball.isColliding(player1.getBounds())) {
                    gameSubject1.removeHealth();
                    fireball.setToBeDestroyed(true);
                } 
            }

            for (auto& fireball : context->getFireballs()) {
                if (fireball.isColliding(player2.getBounds())) {
                    gameSubject2.removeHealth();
                    fireball.setToBeDestroyed(true);
                }
            }

            for (auto& fireball : context->getFireballs()) {
                if (fireball.isColliding(player1.getBounds())) {
                    gameSubject1.removeHealth();
                    fireball.setToBeDestroyed(true);
                }
            }

            for (auto it = items.begin(); it != items.end();) {
                if (player1.isColliding(it->getBounds())) {
                    gameSubject1.addItem();// Add item to player1
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

            
            // Update HUD text
            std::stringstream ss;
            ss << player1Name << " Salud: " << gameSubject1.getHealth() << "\n";
            ss << player1Name << " Items: " << gameSubject1.getItem() << "\n";

            std::stringstream sss;
            sss << player2Name << " salud: " << gameSubject2.getHealth() << "\n";
            sss << player2Name << " Items: " << gameSubject2.getItem() << "\n";

            text.setString(ss.str());
            text.setPosition(10, 10);
            
            text2.setString(sss.str());
            text2.setPosition(800, 10);

            

        }
        

        window.clear(sf::Color::Black);

        if (gameState == INTRO) {//drawing..
                    window.draw(introBackground);
            window.draw(introText);
        } else if (gameState == MENU) {
                    window.draw(menuBackground);
            window.draw(menuText);
        } else if (gameState == PLAYING) {
            level.updateTransition(deltaTime);
            level.draw(window);
            if(!level.getTransition()){
                player1.draw(window);
                player2.draw(window);
                context->draw(window);
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

    // Wait threads to complete
    player1Thread.join();
    player2Thread.join();
    enemyThread.join();

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
