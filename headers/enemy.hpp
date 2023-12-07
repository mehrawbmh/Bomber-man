#ifndef BOMBER_MAN_ENEMY
#define BOMBER_MAN_ENEMY
#include "person.hpp"
#include "random_generator.hpp"

enum EnemyTypes {HORIZONtAL = 0,VERTICAL,NROFTYPES};
enum InitialDirectionTypes {UP_LEFT = 0, DOWN_RIGHT,NROFTYPES};
class Enemy: public Person {
private:

    const std::string UP_TEXTURE_FILE = "sprites/girl/up.png";
    const std::string dOWN_TEXTURE_FILE = "sprites/girl/down-stay.png";
    const std::string LEFT_TEXTURE_FILE = "sprites/girl/left.png";
    const std::string RIGHT_TEXTURE_FILE = "sprites/girl/right.png";
    int type;
    int initialDir;
    void initInitialDirection();
    void initTexture();
public:
    Enemy(float x,float y, float previous_x,float previous_y);
    void update(const sf::RenderTarget* target);
    void updatePosition();
};

#endif