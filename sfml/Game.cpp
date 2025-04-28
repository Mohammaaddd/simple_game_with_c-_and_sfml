#include "Game.h"
//constructor
Game::Game()
{
	this->initFonts();
	this->initText();
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->botServer.init();
	this->launchBotScript();
}

const bool Game::running() const
{
	return this->window->isOpen();
}




void Game::diffuclity()
{
	switch (this->points)
	{
	case 10:
		this->enemyMaxSpeed = 3;
		this->diffcult = "Normal";
		break;
	case 25:
		this->enemyMaxSpeed = 5;
		this->diffcult = "Hard";
		break;
	case 50:
		this->enemyMaxSpeed = 7;
		this->maxEnemies=10;
		this->diffcult = "VeryHard";
		break;
	
	default:
		break;
	}
}

//private functions
void Game::initEnemies()
{
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	//this->enemy.setFillColor(sf::Color::Blue);
	/*this->enemy.setOutlineColor(sf::Color::Blue);
	this->enemy.setOutlineThickness(3.f);*/
	this->enemy.setPosition(10.f, 10.f);
	//this->enemy.setOrigin(sf::Vector2f(25.f, 25.f));

}

void Game::initVariables()
{
	this->diffcult = "Easy";
	this->window = nullptr;
	this->health = 10;
	this->enemySpeed = 1.0f;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->enemyMaxSpeed = 2;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("static/PlaywriteAUSA-Light.ttf"))
		std::cout << "Error";
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode,"I WANT DIE, I HATE LIFE");
	this->window->setFramerateLimit(60);
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::Blue);
	
}



void Game::botClickAt(sf::Vector2f position)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].getGlobalBounds().contains(position)) {
			enemies.erase(enemies.begin() + i);
			enemiesSpeed.erase(enemiesSpeed.begin() + i);
			points++;
			break;
		}
	}
}

sf::RenderWindow* const Game::getWindow()
{
	return this->window;
}

std::vector<sf::RectangleShape> Game::getEnemies()
{
	return this->enemies;
}

//public funtions
void Game::spawnEnemies()
{
	this->enemy.setPosition(rand() % static_cast<int>((this->window->getSize().x - this->enemy.getSize().x)), -6.0f);

	this->enemy.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	this->enemies.push_back(this->enemy);
	this->enemySpeed = rand() % this->enemyMaxSpeed + 1;
	this->enemiesSpeed.push_back(this->enemySpeed);
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		/*case sf::Event::MouseButtonPressed:
			if (this->event.mouseButton.button == sf::Mouse::Left) 
			{
				std::cout << "x position: " << this->event.mouseButton.x << "\ny position: " << this->event.mouseButton.y << std::endl;
				this->enemy.setPosition(sf::Vector2f((float)this->event.mouseButton.x, (float)this->event.mouseButton.y));
			}*/
		}
	}
}

void Game::showGO()
{
	this->gameOverMessage.setFont(this->font);
	this->gameOverMessage.setString("Game Over");
	this->gameOverMessage.setFillColor(sf::Color::Red);
	this->gameOverMessage.setCharacterSize(48);

	// Calculate the bounds of the text
	sf::FloatRect textBounds = this->gameOverMessage.getLocalBounds();

	// Center the text
	this->gameOverMessage.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	this->gameOverMessage.setPosition(this->window->getSize().x / 2.0f,
		this->window->getSize().y / 2.0f);
}

std::vector<sf::Vector2f> Game::getEnemyPositions() const
{
	std::vector<sf::Vector2f> positions;
	for (const auto& enemy : this->enemies)
	{
		positions.push_back(enemy.getPosition());
	}
	return positions;
}

void Game::handleClick(sf::Vector2f clickPos)
{
	std::ofstream log("training_data.txt", std::ios::app);

	log << "STATE";
	for (const auto& enemy : this->enemies)
	{
		log << " " << enemy.getPosition().x << " " << enemy.getPosition().y;
	}

	log << " ACTION " << clickPos.x << " " << clickPos.y << "\n";

	log.close();
}

void Game::launchBotScript()
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Command line
	LPSTR commandLine = (LPSTR)"python \"D:\\Visual studio\\sfml_game\\sfml_game\\sfml_game.py\"";  // Editable string

	// Launch the process
	if (!CreateProcessA(
		NULL,
		commandLine, // command line (must be writable)
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW, // 0 if you want to see the Python console
		NULL, NULL,
		&si, &pi
	)) {
		MessageBoxA(NULL, "Failed to start bot script", "Error", MB_OK);
	}
	else {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::Update()
{
	
	this->pollEvent();

	if (!this->endGame)
	{
		this->diffuclity();
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
	}
	
	if (this->health <= 0)
	{
		this->updateText();
		this->endGame = true;
		this->showGO();
	}

	this->botServer.sendEnemyPosition(this->enemies);

	float x, y;
	if(this->botServer.receiveClick(x,y))
	{
		this->botClickAt(sf::Vector2f(x, y));
	}
	
	//this->handleClick(mousePosView);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl << "Health: " << this->health << std::endl << "Diffculty: " << this->diffcult;
	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn tthe enemy and reset the timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.0f;
		}
	}
		for (int i = 0;i < this->enemies.size(); i++)
		{
			

			this->enemies[i].move(0.0f,this->enemiesSpeed[i]);

			if (this->enemies[i].getPosition().y > this->window->getSize().y)
			{
				this->enemies.erase(this->enemies.begin() + i);
				this->enemiesSpeed.erase(this->enemiesSpeed.begin() + i);
				this->health--;
				//std::cout << "Health: " << this->health << std::endl;
			}
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mouseHeld == false) 
			{
				this->mouseHeld = true;
				bool deleted = false;
				for (int i = 0; i < enemies.size() && deleted == false; i++)
				{

					if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
					{
						deleted = true;
						this->enemies.erase(this->enemies.begin() + i);
						this->enemiesSpeed.erase(this->enemiesSpeed.begin() + i);

						this->points++;
						//std::cout << "points: " << points << std::endl;
					}
				}
				
			}
		}
		else
		{
			this->mouseHeld = false;
		}
}

void Game::render()
{
	this->window->clear(sf::Color::Yellow);

	
	//this->window->draw(this->enemy);
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();


}
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->gameOverMessage);
}	
void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
//destructor
Game::~Game()
{
	delete this->window;
	botServer.close();
}
