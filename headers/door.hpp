#ifndef BOMBER_MAN_DOOR_HPP
#define BOMBER_MAN_DOOR_HPP

#include "map_element.hpp"

class Door: public MapElement {
private:
    bool isPlayerEntered = false;

public:
    Door(const sf::Vector2f &position, sf::Sprite _sprite);

    void draw(sf::RenderTarget *window) override;

    void setPlayerEntered(bool);

    bool hasBeenEntered() const;
};

#endif
