#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Platform.hpp"
#include "MountainPlatform.hpp"
#include "LevelPlatform.hpp"
// #include "BushPlatform.hpp" // Descomentar si se usa BushPlatform

class Level {
private:
    std::vector<Platform*> platforms;
    const int TILE_SIZE = 32;
    const int LEVEL_WIDTH = 56;
    const int LEVEL_HEIGHT = 15;
    std::vector<std::string> levels;
    int currentLevelIndex;
    sf::Texture transitionTexture;
    sf::Sprite transitionSprite;
    bool transitioning;
    float transitionTime;
    int screenWidth;
    int screenHeight;

public:
    Level(int mapOffsetX, int mapOffsetY, int screenWidth, int screenHeight)
        : currentLevelIndex(0), transitioning(false), transitionTime(0.0f), screenWidth(screenWidth), screenHeight(screenHeight) {
        // Añadir 10 niveles
        for (int i = 0; i < 10; ++i) {
            if (i == 0) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^"
                    "........................................................"
                    "........................................................"
                    "........................................................"
                    "............................*..........................."
                    "....^^^....^^..^....^^^....^^^....^^^.....^^^...^......."
                    "........................................................"
                    "........................................................"
                    "...........................................^............"      
                    "........................................................"
                    "......^..^^^^..^...............^.....^..^....^.........."
                    "........................................................"
                    "........................................................"
                    "........................................................"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 1) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^.....................................^"
                    "^..........................................^...........^"      
                    "^.........*.......^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 2) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^"
                    "^......................................................^"
                    "^....^^^^^^^^^.................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.............^^^^.....................................^"
                    "^....................*.....................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 3) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..^^^^........................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^...........^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^.....................................^"
                    "^..........................................^...........^"      
                    "^................^^^^^^^.......*.......................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 4) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^.....................*....................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 5) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^..........................*...........................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^..........................................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 6) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^.......................*..................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 7) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^...^^^....^^..^....^^^....^^^....^^^.....^^^...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^........................*.................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            else if (i == 8) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^..........^^..^................................^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^.......................*..................^...........^"      
                    "^.................^^^^^^^..............................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            /*else if (i == 9) {
                levels.push_back(
                    "^^^^^^^^^^^^^^^^^^...^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                    "^......................................................^"
                    "^..............................^^^^^^^^................^"
                    "^......................................................^"
                    "^......................................................^"
                    "^..........^^..^............................*...^......^"
                    "^......................................................^"
                    "^.........^^^^^^^^...........................^^^^^^^...^"
                    "^..........................................^...........^"      
                    "^.................^^^^^^^............*.................^"
                    "^.....^..^^^^..^...............^.....^..^....^.........^"
                    "^......................................................^"
                    "^......................................................^"
                    "^........................^.............................^"
                    "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
                );
            }
            */
        }

        if (!transitionTexture.loadFromFile("/directorio/game-cc2/images/cargando.png")) {
            std::cerr << "Error: Failed to load transition texture!" << std::endl;
            exit(EXIT_FAILURE);
        }

        transitionSprite.setTexture(transitionTexture);
        transitionSprite.setPosition((screenWidth - transitionTexture.getSize().x) / 2, (screenHeight - transitionTexture.getSize().y) / 2);

        loadLevel(mapOffsetX, mapOffsetY);
    }

    ~Level() {
        for (auto& platform : platforms) {
            delete platform;
        }
    }

    void loadLevel(int mapOffsetX, int mapOffsetY, int levelIndex = 0) {
        platforms.clear();
        currentLevelIndex = levelIndex;
        const std::string& level_data = levels[currentLevelIndex];
        std::cout<<"Nivel : "<<currentLevelIndex<<std::endl;
        for (int y = 0; y < LEVEL_HEIGHT; ++y) {
            for (int x = 0; x < LEVEL_WIDTH; ++x) {
                char tile = level_data[y * LEVEL_WIDTH + x];
                if (tile != '.') {
                    sf::Vector2f position(x * TILE_SIZE + mapOffsetX, y * TILE_SIZE + mapOffsetY);
                    Platform* platform;
                    if (tile == '^') {
                        platform = new MountainPlatform(sf::Vector2f(TILE_SIZE, TILE_SIZE), position);
                    } else if (tile == '*') {
                        platform = new LevelPlatform(sf::Vector2f(TILE_SIZE, TILE_SIZE), position);
                    } // else if (tile == '*') {
                        // platform = new BushPlatform(sf::Vector2f(TILE_SIZE, TILE_SIZE), position);
                    // }
                    platforms.push_back(platform);
                }
            }
        }
    }

    const std::vector<Platform*>& getPlatforms() const {
        return platforms;
    }
    int getLevel() const{
        return currentLevelIndex;
    }
    bool getTransition()const{
        return transitioning;
    }

    void draw(sf::RenderWindow& window) {
        if (transitioning) {
            window.clear(sf::Color(128, 128, 128)); // Fondo gris
            window.draw(transitionSprite);
        } else {
            for (auto& platform : platforms) {
                platform->draw(window);
            }
        }
    }

    bool checkLevelTransition(const sf::FloatRect& playerBounds) {
        for (auto& platform : platforms) {
            LevelPlatform* levelPlatform = dynamic_cast<LevelPlatform*>(platform);
            if (levelPlatform && levelPlatform->checkCollision(playerBounds)) {
                if(currentLevelIndex>= 0 || currentLevelIndex<= 8){
                    /*if(currentLevelIndex == 8){
                        currentLevelIndex = 0;
                    }else{*/
                        currentLevelIndex += 1;
                    //}
                }
                //currentLevelIndex = (currentLevelIndex + 1) % levels.size();
                transitioning = true;
                return true;
            }
        }
        return false;
    }

    void updateTransition(float deltaTime) {
        if (transitioning) {
            transitionTime += deltaTime;
            if (transitionTime > 2.0f) { // 2 segundos de transición
                transitioning = false;
                transitionTime = 0.0f;
            }
        }
    }

    
};

#endif
