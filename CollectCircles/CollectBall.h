#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class CollectBall
{
private:
	sf::CircleShape shape;

	int type;

	void initShape(const sf::RenderWindow& window);

public:
	CollectBall(const sf::RenderWindow& window, int type);
	virtual ~CollectBall();

	//Accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

