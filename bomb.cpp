#include "headers/bomb.hpp"
#include <iostream>
#include <cmath>

Bomb::Bomb(const sf::Vector2f &position, const std::string &textureFilePath) : MapElement(position) {
    if (!this->texture.loadFromFile(textureFilePath)) {
        throw std::runtime_error("error: bomb picture not found!\n");
    }
    this->texture.setSmooth(true);
    this->sprite.setTexture(texture);

    float centerX = std::round(position.x / 100.f) * 100;
    float centerY = std::round(position.y / 100.f) * 100;

    this->position = sf::Vector2f(centerX, centerY);
    this->sprite.setPosition(this->position);
    this->destructionStartRange = sf::Vector2f(centerX - DEFAULT_SPRITE_SIZE.x, centerY - DEFAULT_SPRITE_SIZE.y);
    this->destructionEndRange = sf::Vector2f(centerX + DEFAULT_SPRITE_SIZE.x, centerY + DEFAULT_SPRITE_SIZE.y);
    this->plantTime = std::time(nullptr);
}

bool Bomb::isExploded() const {
    return this->hasExploded;
}

void Bomb::explode() {
    std::cout << "Bomb is exploding...\n";
    this->hasExploded = true;
}

bool Bomb::isTimeToExplode() const {
    return std::time(nullptr) >= this->plantTime + BOMB_EXPLOSION_TIME_SECONDS;
}

bool Bomb::shouldDestroy(sf::Vector2f objectPosition) const {
    if (objectPosition.x > destructionStartRange.x && objectPosition.x < destructionEndRange.x) {
        return objectPosition.y >= destructionStartRange.y && objectPosition.y <= destructionEndRange.y;
    }

    if (objectPosition.x == destructionStartRange.x || objectPosition.x == destructionEndRange.x) {
        return objectPosition.y > destructionStartRange.y && objectPosition.y < destructionEndRange.y;
    }

    return false;
}

void Bomb::draw(sf::RenderTarget *window) {
    this->sprite.setPosition(this->position);
    if (!this->hasExploded)
        window->draw(this->sprite);
}
