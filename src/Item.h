#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>

class Item {
public:
    Item(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const; // Aquí agregamos const

private:
    sf::Sprite sprite;
};

#endif // ITEM_H

