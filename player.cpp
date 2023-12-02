#include "headers/player.hpp"

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}
void Player::initVariables()
{
	this->movementSpeed = 15.f;
	this->hp = 2;
}
void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}
void Player::updatePosition()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //TODO: add arrow keys?
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}
void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);

	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}
void Player::update(const sf::RenderTarget* target)
{
	this->updatePosition();
	this->updateWindowBoundsCollision(target);
}
void Player::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}