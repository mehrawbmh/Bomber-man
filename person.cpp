#include "headers/person.hpp"
#include "headers/breakable_wall.hpp"

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

sf::Vector2f Person::getPosition() {
    return {this->previous_x, this->previous_y};
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

int Person::updateCollision(std::vector<MapElement*> elements) {
	int collision_happened=0;
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
				collision_happened=1;
                break;
            case MapElementTypes::BREAKABLE_WALL: {
                auto breakable = dynamic_cast<BreakableWall *>(elements[i]);
                if (!breakable->isBrokenBefore()) {
                    this->undoMovement();
                    collision_happened = 1;
                }
                break;
            }
            default:
                break;
            }
        }
    }
	return collision_happened;
}
