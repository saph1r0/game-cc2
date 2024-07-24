#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"
#include "Nitem.h"
#include "Platform.hpp"

class ItemFactory {
public:
    static void createItems(const sf::Texture& texture, std::vector<Item>& items, int itemWidth, int itemHeight, int numItems, const std::vector<Platform*>& platforms, float scale);
    static void createNitems(const sf::Texture& texture, std::vector<Nitem>& nitems, int itemWidth, int itemHeight, int numNitems, const std::vector<Platform*>& platforms, float scale);
};

#endif // ITEMFACTORY_H
