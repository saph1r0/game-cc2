#include "Nitem.h"

Nitem::Nitem(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position, float scale) {
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}

void Nitem::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Nitem::getBounds() const {
    return sprite.getGlobalBounds();
}
