#pragma once
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include <iostream>
#include <string>
#include <vector>
#include "Platform.h"
#include "Enemy.h"

class Game
{
private:
	sf::Sprite Background_sprite;
	sf::Texture Background_texture;
	
	sf::Music Soundtrack;

	sf::View View;

	std::unique_ptr<Character> Player;

	std::vector<Platform*> Platforms;
	int catePlatforms;

	std::vector<Enemy<int>*> Enemies;
	int catiEnemies;

	void displayEnemies();
	void displayPlatforms();
	void checkPlatformsCollision();
	void checkEnemyCollision();
	void checkEnemyPlatformCollision();

	sf::RenderWindow window;
	sf::Event event;

	void initSoundtrack();
	void initWindow();
	void initBackground(std::string textura);
	void initView();
	void updateView();
	void initPlatforms();
	void initEnemies();
	void initPlayer();

	Game();

	static Game* instancePtr;

public:

	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;

	static Game& get_game()
	{
		static Game Game;
		return Game;
	}
};

