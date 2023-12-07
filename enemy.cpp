#include "headers/enemy.hpp"

Enemy::Enemy(float x,float y, float previous_x,float previous_y):Person(x,y,x,y)
{
    this->initTexture();
    this->initInitialDirection();
    if(this->initialDir==InitialDirectionTypes::UP_LEFT){
        this->movementSpeed=-this->movementSpeed;
    }
}
void Enemy::initTexture()
{
    if(!this->upwards_texture.loadFromFile(UP_TEXTURE_FILE)){
		std::cout << "Failed to load enemy up texture\n";
    }if(!this->downwards_texture.loadFromFile(dOWN_TEXTURE_FILE)){
		std::cout << "Failed to load enemy down texture\n";
	}
	if(!this->right_texture.loadFromFile(RIGHT_TEXTURE_FILE)){
		std::cout << "Failed to load enemy right texture\n";
	}
	if(!this->left_texture.loadFromFile(LEFT_TEXTURE_FILE)){
		std::cout << "Failed to load enemy left texture\n";
	}
}
void Enemy::update(const sf::RenderTarget* target)
{
    this->updatePosition();
    if(updateWindowBoundsCollision(target)){
        this->movementSpeed=-this->movementSpeed;
    }
}
void Enemy::initInitialDirection()
{
    RandomNumberGenerator rand(0,1);

    if(rand.generateRandomNumber()>=0.5){
        this->initialDir=InitialDirectionTypes::DOWN_RIGHT;
    }else {
        this->initialDir=InitialDirectionTypes::UP_LEFT;
    }
}
void Enemy::updatePosition()
{
    this->savePreviousLocation();
    if(this->type==EnemyTypes::HORIZONtAL){
        this->sprite.move(this->movementSpeed,0.f);
        if(this->movementSpeed>0){
            this->sprite.setTexture(this->right_texture);
        }else{
            this->sprite.setTexture(this->left_texture);
        }
    }else {
        this->sprite.move(0.f,this->movementSpeed);
        if(this->movementSpeed>0){
            this->sprite.setTexture(this->downwards_texture);
        }else {
            this->sprite.setTexture(this->upwards_texture);
        }
    }
}