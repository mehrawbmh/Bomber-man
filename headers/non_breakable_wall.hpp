#ifndef BOMBER_MAN_NON_BREAKABLE_WALL_HPP
#define BOMBER_MAN_NON_BREAKABLE_WALL_HPP

#include "wall.hpp"

class NonBreakableWall: public Wall {
public:
    NonBreakableWall(const sf::Vector2f &position, sf::Sprite _sprite);
    bool canBreak();
};

#endif
