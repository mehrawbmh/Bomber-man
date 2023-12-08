#ifndef PLAYER
#define PLAYER "PLAYER.hpp"

#include "person.hpp"



class Player : public Person {
private:
    int hp = DEFAULT_HP;
    void initTexture();

public:
    static const int MAX_HP = 3;
    static const int DEFAULT_HP = 2;
    bool bombPlanted = false;
    long lastPlantBombTime = 0;

    Player(float x = 0.f, float y = 0.f);

    void updatePosition();
    void updateBomb();
    bool isThrownBomb() const;

    void reduceHp();
    void update(const sf::RenderTarget *target,std::vector<MapElement*> elements);
    int getHp();
};

#endif
