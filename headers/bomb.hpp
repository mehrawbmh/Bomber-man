#ifndef BOMBER_MAN_BOMB_HPP
#define BOMBER_MAN_BOMB_HPP

#include "map_element.hpp"
#include "vector"

const int BOMB_EXPLOSION_TIME_SECONDS = 2;

class Bomb : public MapElement {
private:
    bool hasExploded = false;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f destructionStartRange;
    sf::Vector2f destructionEndRange;
    long plantTime;

public:
    Bomb(const sf::Vector2f &position, std::string textureFilePath);

    void draw(sf::RenderTarget *window) override;

    bool shouldDestroy(sf::Vector2f objectPosition);

    bool isTimeToExplode();

    void explode();

    bool isExploded();
};

#endif
