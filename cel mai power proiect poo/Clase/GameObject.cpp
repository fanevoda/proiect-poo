#include "GameObject.h"

GameObject::GameObject()
{
	xpos = 0.f;
	ypos = 0.f;
	width = 0;
	height = 0;
	speed = 0.f;


	upvelocity = 0.f;
	rightvelocity = 0.f;
}

void GameObject::move(float x, float y)
{
	xpos += x;
	ypos += y;
	sprite.setPosition(xpos, ypos);
}

void GameObject::flipSprite()
{
	sprite.setTextureRect(sf::IntRect(width*2, 0, -width*2, height*2));
}

void GameObject::unflipSprite()
{
	sprite.setTextureRect(sf::IntRect(0, 0, width*2, height*2));
}

void GameObject::resize(float x, float y)
{
	std::cout << "penis";
	sprite.setScale(x, y);

	width = sprite.getTexture()->getSize().x * sprite.getScale().x;
	height = sprite.getTexture()->getSize().y * sprite.getScale().y;

	std::cout << width << " " << height << std::endl;

}

void GameObject::updateSprite(sf::Texture& textura)
{
	texture = textura;
	sprite.setTexture(texture);
	updateWidthHeight();
}

void GameObject::updateSpritenotInit(sf::Texture& textura)
{
	sprite.setTexture(textura);
	updateWidthHeight();
}



void GameObject::updateWidthHeight()
{
	width = sprite.getTexture()->getSize().x * sprite.getScale().x;
	height = sprite.getTexture()->getSize().y * sprite.getScale().y;
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

int GameObject::get_topcoord()
{
	return int(ypos);
}

int GameObject::get_botcoord()
{
	return int(ypos + height);
}
int GameObject::get_leftcoord()
{
	return int(xpos);
}
int GameObject::get_rightcoord()
{
	return int(xpos + width);
}


