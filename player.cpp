#include "headers/player.hpp"

Player::Player(float x, float y)
{
	this->sprite.setPosition(x, y);
	this->previous_x=x;
	this->previous_y=y;
    this->initTexture();
	this->sprite.setTexture(this->downwards_texture);
	this->sprite.setScale(0.9,0.9);
    this->movementSpeed = 3.f;
}

void Player::initTexture()
{
	if(!this->upwards_texture.loadFromFile("sprites/boy/up.png")){
		std::cout << "Failed to load up texture\n";
	}
	if(!this->downwards_texture.loadFromFile("sprites/boy/down-stay.png")){
		std::cout << "Failed to load down texture\n";
	}
	if(!this->right_texture.loadFromFile("sprites/boy/right.png")){
		std::cout << "Failed to load right texture\n";
	}
	if(!this->left_texture.loadFromFile("sprites/boy/left.png")){
		std::cout << "Failed to load left texture\n";
	}
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

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	if (this->sprite.getGlobalBounds().left <= 0.f)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);

	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);

	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);

	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updatePosition();
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
}
void Player::savePreviousLocation()
{
	this->previous_x=this->sprite.getGlobalBounds().left;
	this->previous_y=this->sprite.getGlobalBounds().top;
}
 const sf::Sprite Player::getSprite() const
{
	return this->sprite;
}
void Player::undoMovement()
{
	this->sprite.setPosition(previous_x,previous_y);
}