#include "../include/Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
    delete level1;
}

void Game::startGame()
{
    window.create(sf::VideoMode(1024,768), "MetalZombie",sf::Style::Fullscreen);
    window.setFramerateLimit(500);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }
    }
}
