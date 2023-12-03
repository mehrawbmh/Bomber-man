#ifndef PLAYER
#define PLAYER "PLAYER.hpp"

#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

class Player {
private:
    sf::RectangleShape shape;

    float movementSpeed;
    int hp = 2;

    void initShape();

public:
    static const int MAX_HP = 3;

    Player(float x = 0.f, float y = 0.f);

    void updatePosition();

    void updateWindowBoundsCollision(const sf::RenderTarget *target);

    void update(const sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
};

#endif
