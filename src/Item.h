#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>

class Item {
public:
    Item(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position, float scale);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
};

#endif // ITEM_H

