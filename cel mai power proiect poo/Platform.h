#pragma once

#include "GameObject.h"
#include "Character.h"

class Platform : public GameObject
{
public:
	Platform(float x, float y, std::string adresa_textura);

	bool checkBottomCollision(int bot, int top, int left, int right);
	bool checkLeftCollision(int bot, int top, int left, int right);
	bool checkRightCollision(int bot, int top, int left, int right);
	bool checkUpperCollision(int bot, int top, int left, int right);

	bool checkBottomCollision(Character& Player);
	bool checkLeftCollision(Character& Player);
	bool checkRightCollision(Character& Player);
	bool checkUpperCollision(Character& Player);
};

