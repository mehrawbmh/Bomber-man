#include "headers/wall.hpp"

Wall::Wall(const sf::Vector2f &position): MapElement(position) {}

void Wall::draw(sf::RenderTarget *target) {
    this->sprite.setPosition(this->position);
    target->draw(this->sprite);
}
