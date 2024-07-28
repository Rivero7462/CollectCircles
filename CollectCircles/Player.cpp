#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 10.0f;
	this->hpMax = 10;
	this->hp = hpMax;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.0f, 50.0f));
}

//Constructors / Destructors
Player::Player()
{
	this->initVariables();
	this->initShape();

	//Start position
	this->shape.setPosition(400 - this->shape.getGlobalBounds().width / 2, 300 - this->shape.getGlobalBounds().height / 2);
}

Player::~Player()
{

}

const sf::RectangleShape Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.0f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.0f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	float playerBoundsRight = this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width;
	float playerBoundsBottom = this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height;

	//Left
	if (this->shape.getGlobalBounds().left <= 0.0f)
		this->shape.setPosition(0.0f, this->shape.getGlobalBounds().top);
	//Right
	if (playerBoundsRight >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top
	if (this->shape.getGlobalBounds().top <= 0.0f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.0f);
	//Bottom
	if (playerBoundsBottom >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
