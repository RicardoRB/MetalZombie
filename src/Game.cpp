#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <ctime>

Game::Game()
{
    this->level1 = new Level((char*)"res/sounds/music/level1.ogg",(char*)"res/images/backgrounds/level1/boss.png");
    startGame();
}

Game::~Game()
{
    delete window;
    delete level1;
}

void Game::startGame()
{
    window->create(sf::VideoMode(1024,768), "MetalZombie", sf::Style::Default);
    window->setFramerateLimit(18);
    level1->getPlayer()->camera = window->getDefaultView();
    while (window->isOpen()) {
        //If the player is not moving, then the sprite will draw like standing
        if(!level1->getPlayer()->ismovingLeft() && !level1->getPlayer()->ismovingRight()) {
            level1->getPlayer()->moveRemain();
        }

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
            }
            //Take a screenshot
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                sf::Image Screen = window->capture();
                time_t tSac = time(NULL);
                struct tm* pt1 = localtime(&tSac);
                std::stringstream filename;
                //screenshot with the actually time and date
                filename << "screenshots/MetalZombie-" << pt1->tm_mday << "_" << pt1->tm_mon+1 << "_" << pt1->tm_year+1900 << "_" << pt1->tm_hour << "_" << pt1->tm_min << "_"<< pt1->tm_sec << ".jpg";
                Screen.saveToFile(filename.str());
            }
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100) && (level1->getPlayer()->isEndJumping() && !level1->getPlayer()->isJumping())) {
            level1->getPlayer()->jump();
        } else {
            for(int i = 0; i < (sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
                //If the player is not on the block, he will fall
                //(level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y) + 4)
                //is needed to better collision with the image, I do not need to know the size of the image
                //and the "+4" because the player was floating, same with X position
                if((level1->getPlayer()->sprite.getPosition().y != (level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y) + 4) || (level1->getPlayer()->sprite.getPosition().x > (level1->blocks[(sizeof(level1->blocks)/sizeof(level1->blocks[i]))-1]->getSpriteObject()->getPosition().x + level1->getPlayer()->sprite.getTextureRect().width + 10))) {
                    level1->getPlayer()->falling();
                } else {
                    level1->getPlayer()->setVelY(0);
                    level1->getPlayer()->setEndJumping(true);
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            level1->getPlayer()->attack();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100) {
            level1->getPlayer()->moveRight();
        } else {
            level1->getPlayer()->setmovingRight(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100) {
            level1->getPlayer()->moveLeft();
        } else {
            level1->getPlayer()->setmovingLeft(false);
        }

        window->clear(sf::Color(52,28,27));
        window->setView(level1->getPlayer()->camera);
        //Draw skies
        for(int i = 0; i<(sizeof(level1->skies)/sizeof(level1->skies[i])); i++) {
            window->draw(*level1->skies[i]->getSpriteObject());
        }
        //Draw builders
        for(int i = 0; i<(sizeof(level1->builders)/sizeof(level1->builders[i])); i++) {
            window->draw(*level1->builders[i]->getSpriteObject());
        }
        //Draw the player
        window->draw(level1->getPlayer()->sprite);
        //Draw the blocks
        for(int i = 0; i<(sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
            window->draw(*level1->blocks[i]->getSpriteObject());
        }
        window->display();
    }
}
