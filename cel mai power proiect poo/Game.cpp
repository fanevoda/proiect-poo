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

void Game::initEnemies()
{
    Enemies.push_back(new Enemy<int>(2000, 400, "texturi/enemies/goomba.png"));
    Enemies[0]->resize(0.125f, 0.125f);
    catiEnemies++;


    Enemies.push_back(new Enemy<int>(2500, 400, "texturi/enemies/goomba.png"));
    Enemies[1]->resize(0.125f, 0.125f);
    catiEnemies++;

    Enemies.push_back(new Enemy<int>(2800, 400, "texturi/enemies/goomba.png"));
    Enemies[2]->resize(0.125f, 0.125f);
    catiEnemies++;

}

void Game::initPlatforms()
{
    Platforms.push_back(new Platform(400,420, "texturi/platform/brick.png"));
    Platforms[0]->resize(.125f,.125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(450, 420, "texturi/platform/brick.png"));
    Platforms[1]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(500, 420, "texturi/platform/brick.png"));
    Platforms[2]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(0, 625, "texturi/platform/pamant.png"));
    Platforms[3]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(3410, 625, "texturi/platform/pamant 2.png"));
    Platforms[4]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(4270, 625, "texturi/platform/pamant 3.png"));
    Platforms[5]->resize(3.f, 3.f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(7440, 625, "texturi/platform/pamant 4.png"));
    Platforms[6]->resize(3.f, 3.f);
    catePlatforms += 1;


    Platforms.push_back(new Platform(1150, 430, "texturi/platform/brick.png"));
    Platforms[7]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(950, 430, "texturi/platform/brick.png"));
    Platforms[8]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(1000, 430, "texturi/platform/brick.png"));
    Platforms[9]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(1050, 430, "texturi/platform/brick.png"));
    Platforms[10]->resize(.125f, .125f);
    catePlatforms += 1;

    Platforms.push_back(new Platform(1100, 430, "texturi/platform/brick.png"));
    Platforms[11]->resize(.125f, .125f);
    catePlatforms += 1;



}

void Game::initPlayer()
{
    this->Player = std::make_unique<Character>(620,500,4.f, "texturi/mario/base_mario.png");
    Player->resize(0.5f, 0.5f);

    Player->addNewRunFrame("texturi/mario/mario_run_1.png");
    Player->addNewRunFrame("texturi/mario/mario_run_2.png");
    Player->addNewRunFrame("texturi/mario/mario_run_3.png");
    Player->setJumpingTexture("texturi/mario/mario_jump_1.png");

}

Game::Game()
{
    catePlatforms = 0;
    this->initSoundtrack();
    this->initView();
	this->initWindow();
    this->initBackground("texturi/background/background.png");
    this->initPlatforms();
    this->initEnemies();
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
        Platforms[i]->draw(window);
    
}

void Game::displayEnemies()
{
    for (int i = 0; i < catiEnemies; i++)
    {
        Enemies[i]->update();
        Enemies[i]->draw(window);
    }
}


void Game::checkEnemyPlatformCollision()
{
    for (int i = 0; i < catePlatforms; i++)
    {
        for (int j = 0; j < catiEnemies; j++)
        {
            int bot = Enemies[j]->get_botcoord(), top = Enemies[j]->get_topcoord(), left = Enemies[j]->get_leftcoord(), right = Enemies[j]->get_rightcoord();
            if (Platforms[i]->checkBottomCollision(bot, top, left, right))
            {
                Enemies[j]->setOnSomething();
            }
        }
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

void Game::checkEnemyCollision()
{
    for (int i = 0; i < catiEnemies; i++)
    {
        if (Enemies[i]->checkBottomCollision(*Player))
        {  
            Enemies.erase(Enemies.begin() + i);
            Player->setOnSomething();
            catiEnemies--;
        }
    }
}

void Game::render()
{
    window.clear();

    window.draw(Background_sprite);

    displayEnemies();
    displayPlatforms();
    

    checkPlatformsCollision();
    checkEnemyCollision();
    checkEnemyPlatformCollision();

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
