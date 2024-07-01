#include "Item.h"

Item::Item(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(position);
}

void Item::draw(sf::RenderWindow& window) const { // Aquí agregamos const
    window.draw(sprite);
}
