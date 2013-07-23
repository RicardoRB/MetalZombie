#include "../include/Game.h"
#include <Thor/Animation.hpp>
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
    window->create(sf::VideoMode(1024,768), "MetalZombie");
    //window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false);
    while (this->window->isOpen()) {
        startMenu();
    }
}

Game::~Game() {
    delete window;
    //If the menu igetPosition().xs true, delete them
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

    //Needed to do all animations
    sf::Time frame_time;
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

    // Adjust vertical speed
    if(level1->getPlayer()->isEndJumping()) {
        level1->getPlayer()->setVelY(this->level1->gravity);
    } else if(level1->getPlayer()->getVelY() < this->level1->gravity) {
        level1->getPlayer()->setVelY(level1->getPlayer()->getVelY() + 10.f);
    } else if(level1->getPlayer()->getVelY() > this->level1->gravity) {
        level1->getPlayer()->setVelY(this->level1->gravity);
    }

    // Horizontal movement
    if(level1->getPlayer()->getVelX() > 6.f) {
        level1->getPlayer()->setVelX(level1->getPlayer()->getVelX() - 3.f);
    } else if(level1->getPlayer()->getVelX() < -6.f) {
        level1->getPlayer()->setVelX(level1->getPlayer()->getVelX() + 3.f);
    } else {
        level1->getPlayer()->setVelX(0.f);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && level1->getPlayer()->isLife()) {
        level1->getPlayer()->moveRight();
        level1->moveUI();
    } else {
        level1->getPlayer()->setmovingRight(false);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && level1->getPlayer()->isLife()) {
        level1->getPlayer()->moveLeft();
    } else {
        level1->getPlayer()->setmovingLeft(false);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  && level1->getPlayer()->isEndJumping() && level1->getPlayer()->isLife()) {
        level1->getPlayer()->jump();
    }

    frame_time = frameClock.restart();
    level1->getPlayer()->getSprite()->setPosition(level1->getPlayer()->getSprite()->getPosition().x + level1->getPlayer()->getVelX() * frame_time.asSeconds(),
            level1->getPlayer()->getSprite()->getPosition().y + level1->getPlayer()->getVelY() * frame_time.asSeconds());
    level1->getPlayer()->setPosWindowX(level1->getPlayer()->getSprite()->getPosition().x);

    //Collisions
    for(unsigned int i = 0; i < (sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
        if(level1->blocks[i]->getSpriteObject()->getGlobalBounds().intersects(level1->getPlayer()->getSprite()->getGlobalBounds())) {
            level1->getPlayer()->getSprite()->setPosition(level1->getPlayer()->getSprite()->getPosition().x,
                    level1->blocks[i]->getSpriteObject()->getPosition().y - (level1->getPlayer()->getSprite()->getOrigin().y));
            level1->getPlayer()->setEndJumping(true);
            level1->getPlayer()->setJumping(false);
        }
    }
    if(level1->getPlayer()->isJumping()) {
        level1->getPlayer()->setEndJumping(false);
    }

    //--------------------------------------------------------------------
    //-------------------------Enemy IA-----------------------------------
    //--------------------------------------------------------------------
    for(unsigned int j = 0; j < (sizeof(level1->zombies)/sizeof(level1->zombies[j])); j++) {
        for(unsigned int i = 0; i < (sizeof(level1->blocks)/sizeof(level1->blocks[i])); i++) {
            if(level1->blocks[i]->getSpriteObject()->getGlobalBounds().intersects(level1->zombies[j]->getSprite()->getGlobalBounds())) {
                level1->zombies[j]->getSprite()->setPosition(level1->zombies[j]->getSprite()->getPosition().x,
                        level1->blocks[i]->getSpriteObject()->getPosition().y - (level1->zombies[j]->getSprite()->getOrigin().y));
                level1->zombies[j]->setEndJumping(true);
                level1->zombies[j]->setJumping(false);
            }
        }
        if(level1->zombies[j]->isJumping()) {
            level1->zombies[j]->setEndJumping(false);
        }

        if(level1->zombies[j]->isLife()) {
            if(level1->getPlayer()->isLife() && (level1->zombies[j]->getSprite()->getPosition().x - 40 <= level1->getPlayer()->getSprite()->getPosition().x && level1->zombies[j]->getSprite()->getPosition().x > level1->getPlayer()->getSprite()->getPosition().x) && (level1->zombies[j]->getSprite()->getPosition().y <= level1->getPlayer()->getSprite()->getPosition().y)) {
                level1->zombies[j]->attack(level1->getPlayer());
            } else {
                level1->zombies[j]->moveLeft();
            }
        }
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
        //Collisions with the shot
        //Windows
        if((level1->getPlayer()->getShot()->getPosWindowX() > window->getSize().x || level1->getPlayer()->getShot()->getPosWindowX() < 0)) {
            level1->getPlayer()->setAttacking(false);
            level1->getPlayer()->getShot()->setShot(true);
            level1->getPlayer()->getShot()->endShot();
            //Zombies
        } else {
            for(unsigned int i = 0; i < (sizeof(level1->zombies)/sizeof(level1->zombies[i])); i++) {
                //Condition to kill the zombie if you are looking left or right and Y position of the shot
                if((level1->zombies[i]->isLife() &&
                        level1->getPlayer()->isLookingRight() &&
                        (level1->getPlayer()->getShot()->getSpriteObject()->getPosition().x >= level1->zombies[i]->getSprite()->getPosition().x &&
                         level1->getPlayer()->getShot()->getSpriteObject()->getPosition().y >= level1->zombies[i]->getSprite()->getPosition().y &&
                         level1->getPlayer()->getSprite()->getPosition().x <= level1->zombies[i]->getSprite()->getPosition().x)) ||
                        (level1->zombies[i]->isLife() &&
                         level1->getPlayer()->isLookingLeft() &&
                         (level1->getPlayer()->getShot()->getSpriteObject()->getPosition().x <= level1->zombies[i]->getSprite()->getPosition().x &&
                          level1->getPlayer()->getShot()->getSpriteObject()->getPosition().y >= level1->zombies[i]->getSprite()->getPosition().y &&
                          level1->getPlayer()->getSprite()->getPosition().x >= level1->zombies[i]->getSprite()->getPosition().x))) {
                    //End condition
                    level1->getPlayer()->setAttacking(false);
                    level1->zombies[i]->die();
                    level1->getPlayer()->getShot()->setShot(true);
                    level1->getPlayer()->getShot()->endShot();
                    level1->setContZombies(level1->getContZombies() + 1);
                } else {
                    level1->getPlayer()->getShot()->moveShot(level1->getPlayer()->getShot()->isDirectionRight());
                }
            }
        }
    }

    window->clear(sf::Color(52,28,27));
    window->setView(level1->getPlayer()->getCamera());

    //--------------------------------------------------------------------
    //-------------------------Draw Everything-----------------------------------
    //--------------------------------------------------------------------
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
        if(this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
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
    //Draw shot
    window->draw(*(level1->getPlayer()->getShot()->getSpriteObject()));
    //Draw the player
    level1->getPlayer()->animator.update(frame_time);
    level1->getPlayer()->animator.animate(*level1->getPlayer()->getSprite());
    window->draw(*level1->getPlayer()->getSprite());

    //Draw enemys
    for(unsigned int j = 0; j < (sizeof(level1->zombies)/sizeof(level1->zombies[j])); j++) {
        level1->zombies[j]->animator.update(frame_time);
        level1->zombies[j]->animator.animate(*level1->zombies[j]->getSprite());
        window->draw(*level1->zombies[j]->getSprite());
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
