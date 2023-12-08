#include "headers/player.hpp"

Player::Player(float x, float y): Person(x,y,x,y)
{
    this->initTexture();
	this->sprite.setTexture(this->downwards_texture);
}

void Player::initTexture()
{
	if(!this->upwards_texture.loadFromFile(this->UP_TEXTURE_FILE)){
		std::cout << "Failed to load up texture\n";
	}
	if(!this->downwards_texture.loadFromFile(this->dOWN_TEXTURE_FILE)){
		std::cout << "Failed to load down texture\n";
	}
	if(!this->right_texture.loadFromFile(this->RIGHT_TEXTURE_FILE)){
		std::cout << "Failed to load right texture\n";
	}
	if(!this->left_texture.loadFromFile(this->LEFT_TEXTURE_FILE)){
		std::cout << "Failed to load left texture\n";
	}
}

void Player::updateBomb() {
    if (this->bombPlanted) {
        this->bombPlanted = false;
    } else {
        this->bombPlanted = sf::Keyboard::isKeyPressed(sf::Keyboard::X) && (time(nullptr) > (this->lastPlantBombTime + 1));
        if (this->bombPlanted) {
            this->lastPlantBombTime = time(nullptr);
        }
    }
}

bool Player::isThrownBomb() const {
    return this->bombPlanted;
}

void Player::updatePosition()
{
	this->savePreviousLocation();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->sprite.move(-this->movementSpeed, 0.f);
		this->sprite.setTexture(this->left_texture);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->sprite.setTexture(this->right_texture);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->sprite.move(0.f, -this->movementSpeed);
		this->sprite.setTexture(this->upwards_texture);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->sprite.move(0.f, this->movementSpeed);
		this->sprite.setTexture(this->downwards_texture);
	}
	else
	{
		this->sprite.setTexture(this->downwards_texture);
	}
}

void Player::update(const sf::RenderTarget* target,std::vector<MapElement*> elements)
{
    this->updateBomb();
	this->updatePosition();
	this->updateWindowBoundsCollision(target);
	this->updateCollision(elements);
}

void Player::reduceHp()
{
	this->hp -=1;
	if (this->hp<0){
		this->hp=0;
	}
}

int Player::getHp() const
{
	return this->hp;
}