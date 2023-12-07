#include "headers/person.hpp"

Person::Person(float x,float y,float previous_x,float previous_y)
{
    this->sprite.setPosition(x, y);
    this->movementSpeed = 3.f;

}

int Person::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	if (this->sprite.getGlobalBounds().left <= 0.f){
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x){
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	}
	if (this->sprite.getGlobalBounds().top <= 0.f){
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	}
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y){
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
	}
}
void Person::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
}
const sf::Sprite Person::getSprite() const
{
	return this->sprite;
}

void Person::undoMovement()
{
	this->sprite.setPosition(previous_x,previous_y);
}
void Person::savePreviousLocation()
{
	this->previous_x=this->sprite.getGlobalBounds().left;
	this->previous_y=this->sprite.getGlobalBounds().top;
}
