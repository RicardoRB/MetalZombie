#include "../include/Game.h"

Game::Game()
{
    this->level1 = new Level("res/sounds/music/level1.ogg");
    startGame();
}

Game::~Game()
{
    delete level1;
}

void Game::startGame()
{
    window.create(sf::VideoMode(1024,768), "MetalZombie");
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
        window.draw(level1->player1->sprite);
        window.display();
    }
}
