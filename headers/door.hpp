#ifndef BOMBER_MAN_DOOR_HPP
#define BOMBER_MAN_DOOR_HPP

#include "map_element.hpp"

class Door: public MapElement {
public:
    Door(const sf::Vector2f &position, sf::Sprite _sprite);

    void draw(sf::RenderTarget *window);
};

#endif
