#include "CollectBall.h"

//Private Functions
void CollectBall::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.0f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.0f);
		break;
	}

	this->shape.setFillColor(color);
	this->shape.setPosition(
		sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
		));
}

//Constructors / Destructors
CollectBall::CollectBall(const sf::RenderWindow& window, int type)
	: type(type)	//Initializer. Same as 	this->type = type; Makes sure it happens first.
{
	this->initShape(window);
}

CollectBall::~CollectBall()
{
}

const sf::CircleShape CollectBall::getShape() const
{
	return this->shape;
}

const int& CollectBall::getType() const
{
	return this->type;
}

//Functions
void CollectBall::update(sf::RenderTarget* target)
{

}

void CollectBall::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
