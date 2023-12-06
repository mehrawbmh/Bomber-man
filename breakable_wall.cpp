#include "headers/breakable_wall.hpp"

BreakableWall::BreakableWall(const sf::Vector2f &position, sf::Sprite _sprite): Wall(position) {
    this->sprite = _sprite;
    this->type=MapElementTypes::BREAKABLE_WALL;
}

bool BreakableWall::canBreak() {
    return true;
}
