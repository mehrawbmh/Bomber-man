#ifndef BOMBER_MAN_WALL_HPP
#define BOMBER_MAN_WALL_HPP

#include "map_element.hpp"

class Wall: public MapElement {
public:
    Wall(const sf::Vector2f& position);

    void draw(sf::RenderTarget *window) override;

    virtual bool canBreak() = 0;
};


#endif
