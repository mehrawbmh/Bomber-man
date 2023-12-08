#include "headers/door.hpp"

Door::Door(const sf::Vector2f &position, sf::Sprite _sprite): MapElement(position) {
    this->sprite = _sprite;
}

void Door::draw(sf::RenderTarget *window) {
    if (hasBeenEntered()) {
        this->sprite.setRotation(5.f);
        this->sprite.move(1.f, 1.f);
    }
    this->sprite.setPosition(this->position);
    window->draw(this->sprite);
}

void Door::setPlayerEntered(bool entered) {
    this->isPlayerEntered = entered;
}

bool Door::hasBeenEntered() const {
    return this->isPlayerEntered;
}
