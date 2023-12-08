#include "headers/powerUp.hpp"

PowerUp::PowerUp(PowerUpsTypes _type,sf::Vector2f position): MapElement(position)
{
    this->type = _type;
    this->initTexture(_type);
    this->initSetTexture();
}

void PowerUp::initTexture(PowerUpsTypes _type) {
    switch (_type) {
    case PowerUpsTypes::SPEED_BOOSTER:
        if(!this->texture.loadFromFile(this->SPEED_BOOSTER_FILE)){
		    std::cout << "Failed to load up speed booster texture\n";
	    }
        break;
    case PowerUpsTypes::SYRINGE:
        if(!this->texture.loadFromFile(this->SYRINGE_FILE)){
		    std::cout << "Failed to load up syringe texture\n";
	    }
        break;
    default:
        break;
    }
}

void PowerUp::initSetTexture()
{
    std::cout << "GOT HEREEEEE\n";
    this->sprite.setTexture(this->texture);
}

void PowerUp::draw(sf::RenderTarget *target) {
    std::cout << "DRAWING\n";
    this->sprite.setPosition(this->position);
    target->draw(this->sprite);
}
