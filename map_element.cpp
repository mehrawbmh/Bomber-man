#include "headers/map_element.hpp"

void MapElement::setPosition(const sf::Vector2f &newPosition) {
    this->position = newPosition;
}

MapElement::MapElement(const sf::Vector2f &position): position(position) {}
