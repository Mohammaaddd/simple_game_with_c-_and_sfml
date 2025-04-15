#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//game logic
	std::string diffcult;
	int health;
	unsigned int enemyMaxSpeed;
	bool endGame;
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemySpeed;
	std::vector<float> enemiesSpeed;
	bool mouseHeld;
	
	//Resource
	sf::Font font;


	//gameobjects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//mouseposition
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;	

	//functions
	void diffuclity();
	void initEnemies();
	void initVariables();
	void initFonts();
	void initWindow();
	void initText();

	//Text
	sf::Text uiText;
	sf::Text gameOverMessage;


public:
	//constructor
	Game();
	
	//Access
	const bool running() const;

	//functions
	void spawnEnemies();
	void pollEvent();
	void showGO();

	void updateMousePosition();
	void Update();
	void updateText();
	void updateEnemies();

	void render();
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);

	//destrutor
	~Game();
};

