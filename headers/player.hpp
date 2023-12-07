#ifndef PLAYER
#define PLAYER "PLAYER.hpp"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

class Player {
private:
    sf::Sprite sprite;
    sf::Texture upwards_texture;
    sf::Texture downwards_texture;
    sf::Texture right_texture;
    sf::Texture left_texture;


    float previous_x;
    float previous_y;
    float movementSpeed;
    int hp = DEFAULT_HP;
    bool bombPlanted = false;
    long lastPlantBombTime = 0;
    void initTexture();

public:
    static const int MAX_HP = 3;
    static const int DEFAULT_HP = 2;

    Player(float x = 0.f, float y = 0.f);

    void updatePosition();
    void updateBomb();
    bool isThrownBomb() const;
    void savePreviousLocation();
    const sf::Sprite getSprite() const;

    void updateWindowBoundsCollision(const sf::RenderTarget *target);
    void undoMovement();
    void update(const sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
};

#endif
