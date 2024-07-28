#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.0f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Circle Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!font.loadFromFile("Fonts/AlmostSerious.ttf"))
		std::cout << "ERROR: Didn't load font" << std::endl;
}

void Game::initText()
{
	//Gui Text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("Test");

	//End game text
	this->endText.setFont(this->font);
	this->endText.setFillColor(sf::Color::Red);
	this->endText.setCharacterSize(60);
	this->endText.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
	this->endText.setString("Game Over");
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

const bool Game::running() const
{
	return this->window->isOpen(); //this->endGame == false;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}
//Functions

void Game::spawnBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.0f;
	else
	{
		if (this->balls.size() < this->maxBalls)
		{
			this->balls.push_back(CollectBall(*this->window, this->randBallType()));

			this->spawnTimer = 0.0f;
		}
	}
}

const int Game::randBallType() const
{
	int type = BallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
		type = BallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = BallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;
				break;
			case BallTypes::DAMAGING:
				this->player.takeDamage(5);
				break;
			case BallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			case BallTypes::NROFTYPES:
				this->player.takeDamage(1);
				break;
			}

			//Remove the ball
			this->balls.erase(this->balls.begin() + i);
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << " - Points: " << this->points << "\n"
		<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax();

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//Render Stuff
	this->player.render(this->window);

	for (auto i : this->balls)
	{
		i.render(this->window);
	}

	//Render End Text if game complete
	if (this->endGame)
		this->window->draw(this->endText);

	//Render GUI
	this->renderGui(this->window);
	this->window->display();
}