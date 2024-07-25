//#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"
#include "Platform.hpp"

class ItemFactory {
public:
    static void createItems(const sf::Texture& texture, std::vector<Item>& items, int itemWidth, int itemHeight, int numItems, const std::vector<Platform*>& platforms, float scale);
};
