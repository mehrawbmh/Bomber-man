#ifndef MAP_ELEMENT
#define MAP_ELEMENT "MapElement.hpp"

#include <SFML/Graphics.hpp>

class MapElement {
public:
    MapElement(const sf::Vector2f &position);

    void setPosition(const sf::Vector2f &newPosition);

    virtual void draw(sf::RenderTarget *window) = 0;
    const sf::Sprite getSprite() const;

protected:
    sf::Vector2f position;
    sf::Sprite sprite;
};

#endif
