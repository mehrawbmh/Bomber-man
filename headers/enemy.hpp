#ifndef BOMBER_MAN_ENEMY
#define BOMBER_MAN_ENEMY
#include "person.hpp"
#include "random_generator.hpp"

enum EnemyTypes {HORIZONtAL = 0,VERTICAL};
enum InitialDirectionTypes {UP_LEFT = 0, DOWN_RIGHT};

class Enemy: public Person {
private:
    const std::string UP_TEXTURE_FILE = "sprites/girl/up.png";
    const std::string dOWN_TEXTURE_FILE = "sprites/girl/down-stay.png";
    const std::string LEFT_TEXTURE_FILE = "sprites/girl/left.png";
    const std::string RIGHT_TEXTURE_FILE = "sprites/girl/right.png";

    int type;
    int initialDir;
    bool destroyed = false;

    void initInitialDirection();

    void initTexture();

public:
    Enemy(float x,float y, float previous_x,float previous_y,EnemyTypes _type);

    void update(const sf::RenderTarget* target,std::vector<MapElement*> elements);

    void updatePosition();

    void destroy();

    bool isDestroyed() const;

    void render(sf::RenderTarget *target) override;
};

#endif