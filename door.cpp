#include "headers/door.hpp"

Door::Door(const sf::Vector2f &position, sf::Sprite _sprite): MapElement(position) {
    this->sprite = _sprite;
}

void Door::draw(sf::RenderTarget *window) {
    this->sprite.setPosition(this->position);
    window->draw(this->sprite);
}
