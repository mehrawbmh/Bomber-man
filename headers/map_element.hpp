#ifndef MAP_ELEMENT
#define MAP_ELEMENT "MapElement.hpp"

#include <SFML/Graphics.hpp>


enum MapElementTypes {GRASS = 0, BREAKABLE_WALL, UNBREAKABLE_WALL, NROFTYPES};

class MapElement {
public:
    const sf::Vector2f DEFAULT_SPRITE_SIZE = sf::Vector2f (100.f, 100.f);

    MapElement(const sf::Vector2f &position);

    void setPosition(const sf::Vector2f &newPosition);

    int type;

    virtual void draw(sf::RenderTarget *window) = 0;

    const sf::Sprite getSprite() const;

    sf::Vector2f getPosition() const;

protected:
    sf::Vector2f position;
    sf::Sprite sprite;
};

#endif
