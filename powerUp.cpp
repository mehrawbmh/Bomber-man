#include "headers/powerUp.hpp"

PowerUp::PowerUp(PowerUpsTypes _type,sf::Vector2f position): MapElement(position) {
    this->type = _type;
    this->initTexture(_type);
    this->sprite.setTexture(this->texture);
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

void PowerUp::draw(sf::RenderTarget *target) {
    if (!this->getIsConsumed()) {
        this->sprite.setPosition(this->position);
        target->draw(this->sprite);
    }
}

bool PowerUp::getIsConsumed() {
    return this->isConsumed;
}

void PowerUp::setIsConsumed(bool consumed) {
    this->isConsumed = consumed;
}
