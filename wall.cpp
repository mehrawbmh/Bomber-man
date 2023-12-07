#include "headers/wall.hpp"

Wall::Wall(const sf::Vector2f &position) : MapElement(position) {}

void Wall::draw(sf::RenderTarget *target) {
    if (this->isBroken) return;
    this->sprite.setPosition(this->position);
    target->draw(this->sprite);
}
