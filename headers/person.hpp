#ifndef PERSON
#define PERSON "person.hpp"

#include <SFML/Graphics.hpp>


class Person
{

protected:
    sf::Sprite sprite;
    sf::Texture upwards_texture;
    sf::Texture downwards_texture;
    sf::Texture right_texture;
    sf::Texture left_texture;

    float previous_x;
    float previous_y;
    float movementSpeed;


public:

    Person(float x,float y,float previous_x,float previous_y);

    const sf::Sprite getSprite() const;
    void savePreviousLocation();
    void updateWindowBoundsCollision(const sf::RenderTarget *target);
    void undoMovement();
    void render(sf::RenderTarget *target);
};

#endif