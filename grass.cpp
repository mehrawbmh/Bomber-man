#include "headers/grass.hpp"

Grass::Grass(const sf::Vector2f &position, sf::Sprite _sprite): MapElement(position) {
    this->sprite = _sprite;
}

void Grass::draw(sf::RenderTarget *target) {
    this->sprite.setPosition(this->position);
    target->draw(this->sprite);
}
