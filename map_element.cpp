#include "headers/map_element.hpp"

void MapElement::setPosition(const sf::Vector2f &newPosition) {
    this->position = newPosition;
}

MapElement::MapElement(const sf::Vector2f &position): position(position) {}


const sf::Sprite MapElement::getSprite() const
{
    return this->sprite;
}

sf::Vector2f MapElement::getPosition() const {
    return this->position;
};
