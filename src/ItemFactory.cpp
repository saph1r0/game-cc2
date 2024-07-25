#include "ItemFactory.h"
#include <cstdlib>
#include <ctime>

// Create items and place them on random platforms
void ItemFactory::createItems(const sf::Texture& texture, std::vector<Item>& items, int itemWidth, int itemHeight,
 int numItems, const std::vector<Platform*>& platforms, float scale) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));//random number generator -current time

    for (int i = 0; i < numItems; ++i) {
        int x = (i * itemWidth) % texture.getSize().x;//// Calculate texture rectangle for the item
        int y = ((i * itemWidth) / texture.getSize().x) * itemHeight;

        sf::IntRect rect(x, y, itemWidth, itemHeight);
        const Platform& platform = *platforms[std::rand() % platforms.size()];//boundss platf
        sf::FloatRect bounds = platform.getBounds();
        //above platf
        float posX = bounds.left + static_cast<float>(std::rand() % static_cast<int>(bounds.width - itemWidth));
        float posY = bounds.top - itemHeight; // Arriba de la plataforma
        // Create and add the item to the vector
        items.emplace_back(texture, rect, sf::Vector2f(posX, posY), scale); 
    }
}
