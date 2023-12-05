#include "headers/non_breakable_wall.hpp"

NonBreakableWall::NonBreakableWall(const sf::Vector2f &position, sf::Sprite _sprite) : Wall(position) {
    this->sprite = _sprite;
}

bool NonBreakableWall::canBreak() {
    return false;
}
