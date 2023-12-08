#ifndef BOMBER_MAN_POWER_UPS
#define BOMBER_MAN_POWER_UPS

#include "map_element.hpp"
#include <iostream>

enum PowerUpsTypes {
    SYRINGE = 10, SPEED_BOOSTER = 11
};

class PowerUp : public MapElement {
public:
    void draw(sf::RenderTarget *window) override;

    PowerUp(PowerUpsTypes _type, sf::Vector2f position);

private:
    const std::string SYRINGE_FILE = "sprites/syringe.png";
    const std::string SPEED_BOOSTER_FILE = "sprites/speed_booster.png";

    sf::Texture texture;

    void initSetTexture();

    void initTexture(PowerUpsTypes _type);
};


#endif
