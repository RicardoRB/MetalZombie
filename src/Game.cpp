#include "../include/Game.h"
#include <iostream>

Game::Game() {
    this->level1 = new Level("res/sounds/music/level1.ogg");
    startGame();
}

Game::~Game() {
    delete level1;
}

void Game::startGame() {
    window.create(sf::VideoMode(1024,768), "MetalZombie", sf::Style::Default);
    window.setFramerateLimit(18);
    level1->player1->camera = window.getDefaultView();
    //level1->player1->camera.setCenter((window.getSize().x/2),(window.getSize().y/2) + 333);
    while (window.isOpen()) {

        if(!level1->player1->ismovingLeft() && !level1->player1->ismovingRight()) {
            level1->player1->moveRemain();
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                    sf::Image Screen = window.capture();
                    Screen.saveToFile("screenshots/screenshot.jpg");
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100) {
            level1->player1->moveRight();
            level1->player1->camera.move(level1->player1->getVelX()-5,0);
        } else {
            level1->player1->setmovingRight(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100) {
            level1->player1->moveLeft();
            level1->player1->camera.move(level1->player1->getVelX()+5,0);
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
