#pragma once

#include "GameObject.h"
#include <SFML/Audio.hpp>


class Character : public GameObject
{
private: 

	sf::SoundBuffer JumpingSoundBuffer;
	sf::Sound JumpingSound;

	sf::Texture JumpingTexture;

	std::vector<sf::Texture> RunningAnimations;
	int cateFrameuri;
	int whenSprite;
	int whichSprite;
	bool justjumped = false;
	bool movingRight = false;
	bool movingLeft = false;

	bool onSomething = false;
	bool onRight = false;
	bool onLeft = false;
	bool onHitHead = false;

public:
	Character();
	Character(int x, int y,float speed, std::string adresa_valoare);

	void setMovingRight(bool hm);
	void setMovingLeft(bool hm);

	void addNewRunFrame(std::string adresa_textura);
	void newSpriteSameTexture(int xpos, int ypos);


	void jump();
	bool canJump();
	void setJumpingTexture(std::string adresa_valoare);
	void AddRightMomentum();
	void AddLeftMomentum();
	void setOnSomething();
	void setOnLeft();
	void setOnRight();
	void setOnHitHead();
	void update();
	void updateAnimation();
	
};

