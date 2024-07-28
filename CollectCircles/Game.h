#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "CollectBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;
	
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endText;

	std::vector<CollectBall> balls;
	float spawnTimerMax;
	float spawnTimer;
	int maxBalls;

	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void spawnBalls();
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};

