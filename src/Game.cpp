#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <ctime>

Game::Game() {
    this->window = new sf::RenderWindow();
    this->bufferCameraShot.loadFromFile((char*)"res/sounds/effects/shots/CameraShutterClick-SoundBible-228518582.wav");
    this->soundCameraShot.setBuffer(this->bufferCameraShot);
    this->menuTitle = new Menu();
    this->menu = true;
    this->level1 = NULL;
    window->create(sf::VideoMode(1024,768), "MetalZombie", sf::Style::Default);
    window->setFramerateLimit(18);
    window->setMouseCursorVisible(false);
    while (this->window->isOpen()) {
        startMenu();
    }
}

Game::~Game() {
    delete window;
    //If the menu is true, delete them
    if(this->menu) {
        delete menuTitle;
        delete level1;
    }
}

void Game::startMenu() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100) {
            if(menuTitle->getOption() > 0) {
                menuTitle->playSelect();
                menuTitle->setOption(menuTitle->getOption()-1);
                menuTitle->getOptionIcon()->getSpriteObject()->setPosition(menuTitle->getOptionIcon()->getSpriteObject()->getPosition().x, menuTitle->getOptionIcon()->getSpriteObject()->getPosition().y - 100.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100) {
            if(menuTitle->getOption() < 1) {
                menuTitle->playSelect();
                menuTitle->setOption(menuTitle->getOption()+1);
                menuTitle->getOptionIcon()->getSpriteObject()->setPosition(menuTitle->getOptionIcon()->getSpriteObject()->getPosition().x, menuTitle->getOptionIcon()->getSpriteObject()->getPosition().y + 100.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
            switch(menuTitle->getOption()) {
            case 0:
                this->menuTitle->playStart();
                this->level1 = new Level((char*)"res/sounds/music/level1.ogg");
                level1->getPlayer()->setCamera(window->getDefaultView());
                this->menu = false;
                delete menuTitle;
                while (window->isOpen()) {
                    startGame();
                }
                break;
            default:
                window->close();
                break;
            }
        }

    }
    if(this->menu) {
        window->draw(menuTitle->getTextTitle());
        window->draw(menuTitle->getTextStart());
        window->draw(menuTitle->getTextExit());
        window->draw(*menuTitle->getOptionIcon()->getSpriteObject());
        window->display();
        window->clear();
    }
}

void Game::startGame() {

    //--------------------------------------------------------------------
    //-------------------------Player control-----------------------------
    //--------------------------------------------------------------------
    //If the player is not moving, then the sprite will draw like standing
    if((!level1->getPlayer()->ismovingLeft() && !level1->getPlayer()->ismovingRight()) && level1->getPlayer()->isLife()) {
        level1->getPlayer()->moveRemain();
    }

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
        }
        //Take a screenshot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            this->takeScreenshot();
        }
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100) && (level1->getPlayer()->isEndJumping() && !level1->getPlayer()->isJumping())) {
        if(level1->getPlayer()->isLife()) {
            level1->getPlayer()->jump();
        }
    } else {
        for(unsigned int i = 0; i < (sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
            //If the player is not on the block, he will fall
            //(level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y) + 4)
            //is needed to better collision with the image, I do not need to know the size of the image
            //and the "+4" because the player was floating, same with X position
            if((level1->getPlayer()->getSprite()->getPosition().y != (level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y) + 4) || (level1->getPlayer()->getSprite()->getPosition().x > (level1->blocks[(sizeof(level1->blocks)/sizeof(level1->blocks[i]))-1]->getSpriteObject()->getPosition().x + level1->getPlayer()->getSprite()->getTextureRect().width + 10))) {
                level1->getPlayer()->falling();
            } else {
                level1->getPlayer()->setVelY(0);
                level1->getPlayer()->setEndJumping(true);
            }
        }
    }

    if(((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && !level1->getPlayer()->isAtacking())) {
        if(this->level1->getPlayer()->isLife()) {
            this->level1->getPlayer()->attack();
        } else {

            if(this->level1->getPlayer()->getLives() > 0) {
                this->level1->getPlayer()->setCamera(window->getDefaultView());
                this->level1->restart();
            }
        }
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100)) {
        if(level1->getPlayer()->isLife()) {
            level1->getPlayer()->moveRight();
            level1->moveUI();
        }
    } else {
        level1->getPlayer()->setmovingRight(false);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100)) {
        if(level1->getPlayer()->isLife()) {
            level1->getPlayer()->moveLeft();
        }
    } else {
        level1->getPlayer()->setmovingLeft(false);
    }
    //--------------------------------------------------------------------
    //-------------------------Enemy IA-----------------------------------
    //--------------------------------------------------------------------
    for(unsigned int j = 0; j < (sizeof(level1->zombies)/sizeof(level1->zombies[j])); j++) {
        for(unsigned int i = 0; i < (sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
            //If the player is not on the block, he will fall
            //(level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y) + 4)
            //is needed to better collision with the image, I do not need to know the size of the image
            //and the "+4" because the player was floating, same with X position
            if((level1->zombies[j]->getSprite()->getPosition().y != (level1->blocks[i]->getSpriteObject()->getPosition().y - level1->blocks[i]->getSpriteObject()->getTexture()->getSize().y)) || (level1->zombies[j]->getSprite()->getPosition().x > (level1->blocks[(sizeof(level1->blocks)/sizeof(level1->blocks[i]))-1]->getSpriteObject()->getPosition().x + level1->zombies[j]->getSprite()->getTextureRect().width))) {
                level1->zombies[j]->falling();
            } else {
                level1->zombies[j]->setVelY(0);
            }
        }

        if(level1->zombies[j]->isLife()) {
            if(level1->getPlayer()->isLife() && (level1->zombies[j]->getSprite()->getPosition().x - 40 <= level1->getPlayer()->getSprite()->getPosition().x && level1->zombies[j]->getSprite()->getPosition().x > level1->getPlayer()->getSprite()->getPosition().x) && (level1->zombies[j]->getSprite()->getPosition().y <= level1->getPlayer()->getSprite()->getPosition().y)) {
                level1->zombies[j]->attack(level1->getPlayer());
            } else {
                level1->zombies[j]->moveLeft();
            }
        } else {
            level1->zombies[j]->die();
        }
    }

    window->clear(sf::Color(52,28,27));
    window->setView(level1->getPlayer()->getCamera());
    //Draw skies
    for(unsigned int i = 0; i<(sizeof(level1->skies)/sizeof(level1->skies[i])); i++) {
        window->draw(*level1->skies[i]->getSpriteObject());
    }
    //Draw builders
    for(unsigned int i = 0; i<(sizeof(level1->builders)/sizeof(level1->builders[i])); i++) {
        window->draw(*level1->builders[i]->getSpriteObject());
    }
    //Draw IU
    if(this->level1->getPlayer()->getLives() <= 0 || this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
            if(this->level1->getPlayer()->getSprite()->getPosition().x >= 9900){
                this->level1->getPlayer()->moveRight();
            }
        window->draw(level1->getTextGameOver());
    }
    window->draw(level1->getTextTime());
    window->draw(*level1->getLivesFace()->getSpriteObject());
    window->draw(level1->getTextLives());
    window->draw(*level1->getZombiesFace()->getSpriteObject());
    window->draw(level1->getTextZombies());


    //Draw the blocks
    for(unsigned int i = 0; i<(sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
        window->draw(*level1->blocks[i]->getSpriteObject());
    }
    //Draw soldiers friends
    for(unsigned int i = 0; i<(sizeof(level1->soldiers)/sizeof(level1->soldiers[i])); i++) {
        window->draw(*level1->soldiers[i]->getSpriteObject());
    }
    //Draw the player
    window->draw(*level1->getPlayer()->getSprite());
    //Draw enemys
    for(unsigned int j = 0; j < (sizeof(level1->zombies)/sizeof(level1->zombies[j])); j++) {
        window->draw(*level1->zombies[j]->getSprite());
    }
    if(level1->getPlayer()->isAtacking()) {
        if(level1->getPlayer()->getShot()->isShot()) {
            if(level1->getPlayer()->isLookingRight()) {
                level1->getPlayer()->getShot()->setPosWindowX(level1->getPlayer()->getPosWindowX());
                level1->getPlayer()->getShot()->setDirectionRight(true);
                level1->getPlayer()->getShot()->setShot(false);
            } else {
                level1->getPlayer()->getShot()->setPosWindowX(level1->getPlayer()->getPosWindowX());
                level1->getPlayer()->getShot()->setDirectionRight(false);
                level1->getPlayer()->getShot()->setShot(false);
            }
        }
        window->draw(*(level1->getPlayer()->getShot()->getSpriteObject()));
        //Collisions with the shot
        //Windows
        if((level1->getPlayer()->getShot()->getPosWindowX() > 2020.f || level1->getPlayer()->getShot()->getPosWindowX() < -1460.f)) {
            level1->getPlayer()->setAttacking(false);
            level1->getPlayer()->getShot()->setShot(true);
            level1->getPlayer()->getShot()->endShot();
            //Zombies
        } else {
            for(unsigned int i = 0; i < (sizeof(level1->zombies)/sizeof(level1->zombies[i])); i++) {
                if(level1->zombies[i]->isLife() && level1->getPlayer()->isLookingRight() && (level1->getPlayer()->getShot()->getSpriteObject()->getPosition().x >= level1->zombies[i]->getSprite()->getPosition().x && level1->getPlayer()->getShot()->getSpriteObject()->getPosition().y >= level1->zombies[i]->getSprite()->getPosition().y && level1->getPlayer()->getSprite()->getPosition().x <= level1->zombies[i]->getSprite()->getPosition().x)) {
                    level1->getPlayer()->setAttacking(false);
                    level1->zombies[i]->setLife(false);
                    level1->getPlayer()->getShot()->setShot(true);
                    level1->getPlayer()->getShot()->endShot();
                    level1->setContZombies(level1->getContZombies() + 1);
                } else if (level1->zombies[i]->isLife() && level1->getPlayer()->isLookingLeft() && (level1->getPlayer()->getShot()->getSpriteObject()->getPosition().x <= level1->zombies[i]->getSprite()->getPosition().x && level1->getPlayer()->getShot()->getSpriteObject()->getPosition().y >= level1->zombies[i]->getSprite()->getPosition().y && level1->getPlayer()->getSprite()->getPosition().x >= level1->zombies[i]->getSprite()->getPosition().x)) {
                    level1->getPlayer()->setAttacking(false);
                    level1->zombies[i]->setLife(false);
                    level1->getPlayer()->getShot()->setShot(true);
                    level1->getPlayer()->getShot()->endShot();
                    level1->setContZombies(level1->getContZombies() + 1);
                } else {
                    level1->getPlayer()->getShot()->moveShot(level1->getPlayer()->getShot()->isDirectionRight());
                }
            }
        }
        window->draw(*(level1->getPlayer()->getShot()->getSpriteObject()));
    }
    window->display();
}

void Game::takeScreenshot() {
    this->soundCameraShot.play();
    sf::Image Screen = window->capture();
    time_t tSac = time(NULL);
    struct tm* pt1 = localtime(&tSac);
    std::stringstream filename;
    //screenshot with the actually time and date
    filename << "screenshots/MetalZombie-" << pt1->tm_mday << "_" << pt1->tm_mon+1 << "_" << pt1->tm_year+1900 << "_" << pt1->tm_hour << "_" << pt1->tm_min << "_"<< pt1->tm_sec << ".jpg";
    Screen.saveToFile(filename.str());
}
