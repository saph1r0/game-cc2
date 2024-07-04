#include "Item.h"

Item::Item(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position,float scale) {
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(position);
    sprite.setScale(scale, scale); 
}

void Item::draw(sf::RenderWindow& window) const { 
    window.draw(sprite);
}
sf::FloatRect Item::getBounds() const {
    return sprite.getGlobalBounds();
}