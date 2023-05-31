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

	void displayPlatforms();
	void checkPlatformsCollision();

	sf::RenderWindow window;
	sf::Event event;

	void initSoundtrack();
	void initWindow();
	void initBackground(std::string textura);
	void initView();
	void updateView();
	void initPlatforms();
	void initPlayer();

public:

	Game();
	~Game();

	void update();
	void render();
	const sf::RenderWindow& getWindow() const;
};

