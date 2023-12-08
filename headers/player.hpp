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
    int foundKeys = 0;
    bool doorFound = false;
    void initTexture();
    void updatePosition();
    void updateBomb();

public:
    static const int MAX_HP = 3;
    static const int DEFAULT_HP = 2;
    bool bombPlanted = false;
    long lastPlantBombTime = 0;

    Player(float x = 0.f, float y = 0.f);

    void update(const sf::RenderTarget *target,std::vector<MapElement*> elements);

    bool isThrownBomb() const;

    void reduceHp();

    int getHp() const;

    int getFoundKeys() const;

    void setFoundKeys(int foundKeysCount);

    bool hasFoundTheDoor() const;

    void setDoorFound(bool hasFound);

    void render(sf::RenderTarget *target) override;
};

#endif
