#ifndef PLAYER
#define PLAYER "PLAYER.hpp"

#include "person.hpp"



class Player : public Person {
private:

    const std::string UP_TEXTURE_FILE = "sprites/boy/up.png";
    const std::string dOWN_TEXTURE_FILE = "sprites/boy/down-stay.png";
    const std::string LEFT_TEXTURE_FILE = "sprites/boy/left.png";
    const std::string RIGHT_TEXTURE_FILE = "sprites/boy/right.png";

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
