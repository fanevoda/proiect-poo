#pragma once
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class GameObject
{
protected:

	int width;
	int height;

	float speed;

	float xpos;
	float ypos;

	float upvelocity;
	float rightvelocity;

	sf::Texture texture;
	sf::Sprite sprite;

public:

	GameObject();

	int get_topcoord();
	int get_botcoord();
	int get_leftcoord();
	int get_rightcoord();

	virtual void move(float x, float y);
	virtual void updateSprite(sf::Texture& texture);
	virtual void updateSpritenotInit(sf::Texture& texture);
	virtual void updateWidthHeight();
	virtual void flipSprite();
	virtual void unflipSprite();

	void resize(float x, float y);
    void draw(sf::RenderWindow& window);
};

