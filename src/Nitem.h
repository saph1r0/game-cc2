#ifndef NITEM_H
#define NITEM_H

#include <SFML/Graphics.hpp>

class Nitem {
public:
    Nitem(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& position, float scale);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
};

#endif // NITEM_H
