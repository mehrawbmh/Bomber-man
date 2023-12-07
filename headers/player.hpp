#ifndef PLAYER
#define PLAYER "PLAYER.hpp"

#include "person.hpp"



class Player : public Person {
private:
    int hp = 2;
    void initTexture();

public:
    static const int MAX_HP = 3;

    Player(float x = 0.f, float y = 0.f);

    void updatePosition();


    void update(const sf::RenderTarget *target,std::vector<MapElement*> elements);

};

#endif
