#include "GameObject.h"
#include "Character.h"

template <typename T>
class Enemy : public GameObject
{
private:

	T whenSprite = 0;
	bool OnSomething = false;
	bool right = false;

public:

	Enemy();
	~Enemy();

	Enemy(T x, T y, std::string adresa_textura)
	{
		xpos = x;
		ypos = y;

		rightvelocity = -1.f;
		upvelocity = 0.f;

		try
		{
			if (!texture.loadFromFile(adresa_textura))
				throw "aiaie";
		}
		catch (...)
		{

		}

		this->updateSprite(texture);
	}

	void setOnSomething()
	{
		OnSomething = true;
	}

	void updateAnimation()
	{
		whenSprite++;

		if (whenSprite == 80)
		{
			if (!right)
			{
				sprite.setTextureRect(sf::IntRect(600, 0, -600, 600));
				right = true;
			}
			else
			{
				sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
				right = false;
			}
			whenSprite = 0;
		}
	}

	bool checkBottomCollision(Character& Player)
	{
		if (Player.get_leftcoord() <= width + xpos && Player.get_rightcoord() >= xpos)
			if (Player.get_botcoord() <= ypos + 8 && Player.get_botcoord() >= ypos - 4)
				return true;

		return false;
	}


	void update()
	{

		updateAnimation();

		upvelocity += .0051f;

		if (OnSomething && upvelocity > 0)
			upvelocity = 0;

		OnSomething = false;

		this->move(rightvelocity, upvelocity);

	}



};