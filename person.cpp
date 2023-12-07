#include "headers/person.hpp"

Person::Person(float x,float y,float previous_x,float previous_y)
{
    this->sprite.setPosition(x, y);
    this->movementSpeed = 3.f;

}

int Person::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	int collisionHappened=0;
	if (this->sprite.getGlobalBounds().left <= 0.f){
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
		collisionHappened=1;
	}
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x){
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
		collisionHappened=1;
	}
	if (this->sprite.getGlobalBounds().top <= 0.f){
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
		collisionHappened=1;
	}
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y){
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
		collisionHappened=1;
	}
	return collisionHappened;
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
void Person::updateCollision(std::vector<MapElement*> elements) {
    for(size_t i=0; i< elements.size();i++ ){
        sf::Sprite playerScaledSprite = this->getSprite();
        sf::Sprite elementScaledSprite = elements[i]->getSprite();
        playerScaledSprite.setScale(0.75, 0.75);
        elementScaledSprite.setScale(0.75, 0.75);

        if (playerScaledSprite.getGlobalBounds().intersects(elementScaledSprite.getGlobalBounds())){
            switch (elements[i]->type)
            {
            case MapElementTypes::UNBREAKABLE_WALL:
                this->undoMovement();
                break;
            case MapElementTypes::BREAKABLE_WALL:
                this->undoMovement();
                break;
            default:
                break;
            }
        }
    }
}