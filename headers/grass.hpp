#ifndef BOMBER_MAN_GRASS_HPP
#define BOMBER_MAN_GRASS_HPP

#include "map_element.hpp"

class Grass : public MapElement {
public:
    Grass(const sf::Vector2f &position, sf::Sprite _sprite);

    void draw(sf::RenderTarget *window);
};

#endif
