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
    int hp = 2;
    void initTexture();

public:
    static const int MAX_HP = 3;

    Player(float x = 0.f, float y = 0.f);

    void updatePosition();
    void savePreviousLocation();

    void updateWindowBoundsCollision(const sf::RenderTarget *target);

    void update(const sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
};

#endif
