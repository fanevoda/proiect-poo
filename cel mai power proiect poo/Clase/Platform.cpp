#include "Platform.h"
#include <iostream>

Platform::Platform(float x, float y, std::string adresa_valoare)
{
	xpos = x;
	ypos = y;

	try
	{
		if (!texture.loadFromFile(adresa_valoare))
			throw "aiaie";
	}
	catch (...)
	{
	
	}

	this->updateSprite(texture);

	this->resize(5.f,5.f);

	move(0, 0);

}

bool Platform::checkBottomCollision(Character& Player)
{
	if (Player.get_leftcoord() <= width + xpos && Player.get_rightcoord() >= xpos)
		if (Player.get_botcoord() <= ypos + 8 && Player.get_botcoord() >= ypos - 4)
			return true;

	return false;
}

bool Platform::checkRightCollision(Character& Player)
{

	if (Player.get_botcoord() >= ypos && Player.get_topcoord() <= ypos + height)
		if (Player.get_rightcoord() <= xpos + 5 && Player.get_rightcoord() >= xpos - 2)
		{
			std::cout << "left"; 
			return true;
		}

	return false;
}

bool Platform::checkLeftCollision(Character& Player)
{

	if (Player.get_botcoord() >= ypos && Player.get_topcoord() <= ypos + height)
		if (Player.get_leftcoord() <= xpos + 5 + width && Player.get_leftcoord() >= width + xpos - 2)
			return true;

	return false;
}

bool Platform::checkUpperCollision(Character& Player)
{

	if (Player.get_leftcoord() <= width + xpos && Player.get_rightcoord() >= xpos)
		if (Player.get_topcoord() <= ypos + height + 8 && Player.get_topcoord() >= height + ypos - 4)
			return true;

	return false;
}