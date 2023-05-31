#include "Game.h"
#include <iostream>
#include <memory>

void Game::initSoundtrack()
{
    try
    {
        if (!Soundtrack.openFromFile("soundtrack.wav"))
            throw "na mers";
    }
    catch (...)
    {

    }
    Soundtrack.play();
}

void Game::initView()
{
    View.reset(sf::FloatRect(100, 100, 700, 500));
}

void Game::updateView()
{
    if( (Player->get_leftcoord() + Player->get_rightcoord()) / 2 - 640 > 1 )
        View.reset(sf::FloatRect((Player->get_leftcoord() + Player->get_rightcoord()) / 2 - 640, 0, 1280, 720));
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1280, 720), "My window");
	this->window.setVerticalSyncEnabled(true);
    this->window.setView(View);
}

void Game::initBackground(std::string textura)
{
    try
    {
        if (!Background_texture.loadFromFile(textura))
            throw "aiaie";
    }
    catch (...)
    {

    }

    Background_sprite.setTexture(Background_texture);
    Background_sprite.setScale(3, 3);
}

void Game::initPlatforms()
{
    Platforms.push_back(new Platform(400,400, "platform/brick.png"));
    Platforms[0]->resize(.125f,.125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(450, 400, "platform/brick.png"));
    Platforms[1]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(500, 400, "platform/brick.png"));
    Platforms[2]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(0, 625, "platform/pamant.png"));
    Platforms[3]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(3410, 625, "platform/pamant 2.png"));
    Platforms[4]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(4270, 625, "platform/pamant 3.png"));
    Platforms[5]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(7440, 625, "platform/pamant 4.png"));
    Platforms[6]->resize(3.f, 3.f);
    catePlatforms += 1;

}

void Game::initPlayer()
{
    this->Player = std::make_unique<Character>(620,500,4.f, "mario/base_mario.png");
    Player->resize(0.5f, 0.5f);

    Player->addNewRunFrame("mario/mario_run_1.png");
    Player->addNewRunFrame("mario/mario_run_2.png");
    Player->addNewRunFrame("mario/mario_run_3.png");
    Player->setJumpingTexture("mario/mario_jump_1.png");

}

Game::Game()
{
    catePlatforms = 0;
    this->initSoundtrack();
    this->initView();
	this->initWindow();
    this->initBackground("background/background.png");
    this->initPlatforms();
    this->initPlayer();
}

Game::~Game()
{

}

void Game::update()
{
    // window events go here

    while (this->window.pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case  sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W && Player->canJump())
            {
                Player->jump();
            }

            if (event.key.code == sf::Keyboard::D)
                Player->setMovingRight(true);

            if (event.key.code == sf::Keyboard::A)
                Player->setMovingLeft(true);
            break;



        case sf::Event::KeyReleased:
            
            switch (event.key.code)
            {
            case sf::Keyboard::A:
                Player->setMovingLeft(false);
                break;
            case sf::Keyboard::D:
                Player->setMovingRight(false);
                break;
            }


            break;
        }
    }


   
}void Game::displayPlatforms()
{
    for (int i = 0; i < catePlatforms; i++)
    {
        Platforms[i]->draw(window);
    }
}

void Game::checkPlatformsCollision()
{
    for (int i = 0; i < catePlatforms; i++)
    {
        if (Platforms[i]->checkBottomCollision(*Player))
            Player->setOnSomething();
        if (Platforms[i]->checkLeftCollision(*Player))
            Player->setOnLeft();
        if (Platforms[i]->checkRightCollision(*Player))
            Player->setOnRight();
        if (Platforms[i]->checkUpperCollision(*Player))
            Player->setOnHitHead();
    }
}

void Game::render()
{
    window.clear();

    window.draw(Background_sprite);

    displayPlatforms();
    checkPlatformsCollision();

    Player->update();
    Player->draw(window);

    window.setView(window.getDefaultView());
    
    updateView();

    window.setView(View);

    window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
