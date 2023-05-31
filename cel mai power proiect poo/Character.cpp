#include "Character.h"


Character::Character()
{
	speed = 10.f;
}


Character::Character(int x, int y, float sp, std::string adresa_valoare)
{
	xpos = x;
	ypos = y;

	speed = sp;

	whenSprite = 0;
	whichSprite = 0;
	cateFrameuri = 0;

	try
	{
		if (!texture.loadFromFile(adresa_valoare))
			throw "aiaie";
	}
	catch (...)
	{

	}

	this->updateSprite(texture);


	try
	{
		if (!JumpingSoundBuffer.loadFromFile("mario_jump.wav"))
			throw "na mers";
	}
	catch (...)
	{

	}

	JumpingSound.setBuffer(JumpingSoundBuffer);

}

void Character::jump()
{
	upvelocity = -1.45 * speed;
	justjumped = true;

	JumpingSound.play();

}

bool Character::canJump()
{
	if (upvelocity < 1 && upvelocity > -1)
		return true;
	else
		return false;
}

void Character::setJumpingTexture(std::string adresa_textura)
{
	try
	{
		if (!JumpingTexture.loadFromFile(adresa_textura))
			throw "aiaie";
	}
	catch (...)
	{

	}
}


void Character::AddRightMomentum()
{
	if (rightvelocity <= speed)
		rightvelocity += speed/5;
}

void Character::AddLeftMomentum()
{
	if (rightvelocity >= -speed)
		rightvelocity -= speed/5;
}


void Character::setMovingLeft(bool hm)
{
	movingLeft = hm;

	if (hm)
		flipSprite();
}

void Character::setMovingRight(bool hm)
{
	movingRight = hm;
	if (hm)
		unflipSprite();
}

void Character::setOnLeft()
{
	onLeft = true;
}

void Character::setOnRight()
{
	onRight = true;
}

void Character::setOnSomething()
{
	onSomething = true;
}

void Character::setOnHitHead()
{
	onHitHead = true;
}

void Character::newSpriteSameTexture(int x, int y)
{
	sprite.setTextureRect(sf::IntRect(x, y, 500, 500));
	width = 300;
	height = 300;
}

void Character::addNewRunFrame(std::string adresa_textura)
{
	sf::Texture textura;

	try
	{
		if (!textura.loadFromFile(adresa_textura))
			throw "aiaie";
	}
	catch (...)
	{

	}

	RunningAnimations.push_back(textura);

	cateFrameuri+=1;


}


void Character::updateAnimation()
{
	if (movingLeft || movingRight)
	{
		if (whenSprite == 15)
		{
			whenSprite = 0;

			whichSprite++;

			if (whichSprite == cateFrameuri)
				whichSprite = 0;

			updateSpritenotInit(RunningAnimations[whichSprite]);
		}
		whenSprite++;
	}
	else
	{
		updateSprite(texture);
	}

}

void Character::update()
{
	upvelocity += speed/50;
	
	rightvelocity -= rightvelocity / 5;

	// try to make animation ig

	updateAnimation();

	// check for stanga dreapta movement

	if (movingRight)
	{
		AddRightMomentum();
	}
	if (movingLeft)
	{
		AddLeftMomentum();
	}

	if (xpos <= 0 && rightvelocity < 0)
		rightvelocity = 0;

	if (width + xpos >= 12000 && rightvelocity > 0)
		rightvelocity = 0;


	// check for ground collision

	//if (height + ypos >= 720 && !justjumped)
	//{
	//	upvelocity = 0;
	//}

	if (onSomething && upvelocity > 0)
		upvelocity = 0;

	if (onRight && rightvelocity > 0)
		rightvelocity = 0;

	if (onLeft && rightvelocity < 0)
		rightvelocity = 0;

	if (onHitHead && upvelocity <= 0)
		upvelocity = 0;

	onLeft = false;
	onRight = false;
	onSomething = false;
	onHitHead = false;
	justjumped = false;

	this->move(rightvelocity, upvelocity);

	if (upvelocity != 0)
		updateSpritenotInit(JumpingTexture);

}