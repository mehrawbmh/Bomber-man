#ifndef BOMBER_MAN_BREAKABLE_WALL_HPP
#define BOMBER_MAN_BREAKABLE_WALL_HPP

#include "wall.hpp"

class BreakableWall : public Wall {
public:
    BreakableWall(const sf::Vector2f &position, sf::Sprite _sprite);

    bool canBreak() override;

    void destroy() override;

    bool isBrokenBefore();
};

#endif
