
#ifndef BOMBER_MAN_POWER_UPS
#define BOMBER_MAN_POWER_UPS

#include "map_element.hpp"
#include <iostream>
enum PowerUpsTypes {SYRINGE = 0,SPEED_BOOSTER};
class PowerUp:public MapElement{
public:

private:
    const std::string SYRINGE_FILE = "sprites/syringe.png";
    const std::string SPEED_BOOSTER_FILE = "sprites/speed_booster.png";

    sf::Texture texture;

    PowerUp(PowerUpsTypes _type);

    void initSetTexture();
    void initTexture(PowerUpsTypes _type);
};







#endif