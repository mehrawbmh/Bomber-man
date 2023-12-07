#include "headers/key.hpp"

Key::Key(const sf::Vector2f &position, sf::Sprite _sprite): MapElement(position) {
    this->sprite = _sprite;
    this->type=MapElementTypes::GRASS;
}

void Key::draw(sf::RenderTarget *target) {
    this->sprite.setPosition(this->position);
    target->draw(this->sprite);
}
