#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Character.h"
#include "Game.h"

int main()
{
    auto& game = Game::get_game();

    while (game.getWindow().isOpen())
    {
       game.update();
       game.render();
    }

    return 0;
}