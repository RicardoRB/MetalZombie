#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <ctime>

Game::Game()
{
    this->level1 = new Level("res/sounds/music/level1.ogg","res/images/backgrounds/background_level1.png");
    startGame();
}

Game::~Game()
{
    delete level1;
}

void Game::startGame()
{
    window.create(sf::VideoMode(1024,768), "MetalZombie", sf::Style::Default);
    window.setFramerateLimit(18);
    level1->player1->camera = window.getDefaultView();
    //To start the picture since the begin
    level1->background.setPosition(0,0);
    while (window.isOpen()) {
        //If the player is not moving, then the sprite will draw like standing
        if(!level1->player1->ismovingLeft() && !level1->player1->ismovingRight()) {
            level1->player1->moveRemain();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                //Take a screenshot
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                    sf::Image Screen = window.capture();
                    time_t tSac = time(NULL);
                    struct tm* pt1 = localtime(&tSac);
                    std::stringstream filename;
                    //screenshot with the actually time and date
                    filename << "screenshots/MetalZombie-" << pt1->tm_mday << "_" << pt1->tm_mon+1 << "_" << pt1->tm_year+1900 << "_" << pt1->tm_hour << "_" << pt1->tm_min << "_"<< pt1->tm_sec << ".jpg";
                    Screen.saveToFile(filename.str());
                }
            }
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100) && (level1->player1->isEndJumping() && !level1->player1->isJumping())) {
            level1->player1->jump();
        } else {
            level1->player1->falling();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100) {
            level1->player1->moveRight();
        } else {
            level1->player1->setmovingRight(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100) {
            level1->player1->moveLeft();
        } else {
            level1->player1->setmovingLeft(false);
        }

        window.clear();
        window.setView(level1->player1->camera);
        window.draw(level1->background);
        window.draw(level1->player1->sprite);
        window.display();
    }
}
