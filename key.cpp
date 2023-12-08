#include "headers/key.hpp"

Key::Key(const sf::Vector2f &position, sf::Sprite _sprite): MapElement(position) {
    this->sprite = _sprite;
    this->type=MapElementTypes::GRASS;
}

void Key::draw(sf::RenderTarget *target) {
    if (!this->isTaken()) {
        this->sprite.setPosition(this->position);
        target->draw(this->sprite);
    }
}

bool Key::isTaken() const {
    return this->hasTakenByPlayer;
}

void Key::setIsTaken(bool isTaken) {
    this->hasTakenByPlayer = isTaken;
}
