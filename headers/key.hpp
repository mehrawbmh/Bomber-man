#ifndef BOMBER_MAN_KEY_HPP
#define BOMBER_MAN_KEY_HPP

#include "map_element.hpp"

class Key : public MapElement {
public:
    Key(const sf::Vector2f &position, sf::Sprite _sprite);

    void draw(sf::RenderTarget *window) override;
};

#endif
