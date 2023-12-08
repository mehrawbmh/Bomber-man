#include "headers/enemy.hpp"

Enemy::Enemy(float x,float y, float previous_x,float previous_y,EnemyTypes _type) : Person(x,y,x,y)
{
    this->type=_type;
    this->initTexture();
    this->initInitialDirection();
    if(this->initialDir==InitialDirectionTypes::UP_LEFT){
        this->movementSpeed=-this->movementSpeed;
    }
}
void Enemy::initTexture()
{
    if(!this->upwards_texture.loadFromFile(this->UP_TEXTURE_FILE)){
		std::cout << "Failed to load enemy up texture\n";
    }if(!this->downwards_texture.loadFromFile(this->dOWN_TEXTURE_FILE)){
		std::cout << "Failed to load enemy down texture\n";
	}
	if(!this->right_texture.loadFromFile(this->RIGHT_TEXTURE_FILE)){
		std::cout << "Failed to load enemy right texture\n";
	}
	if(!this->left_texture.loadFromFile(this->LEFT_TEXTURE_FILE)){
		std::cout << "Failed to load enemy left texture\n";
	}
}
void Enemy::update(const sf::RenderTarget* target,std::vector<MapElement*> elements)
{
    this->updatePosition();
    if(this->updateWindowBoundsCollision(target)||this->updateCollision(elements)){
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

void Enemy::destroy() {
    this->destroyed = true;
}

bool Enemy::isDestroyed() const {
    return this->destroyed;
}

void Enemy::render(sf::RenderTarget *target) {
    if (!this->isDestroyed()) {
        target->draw(this->sprite);
    }
}
