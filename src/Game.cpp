#include "../include/Game.h"
#include <Thor/Animation.hpp>
#include <iostream>
#include <sstream>
#include <ctime>

Game::Game() {
    window = new sf::RenderWindow();
    this->bufferCameraShot.loadFromFile((char*)"res/sounds/effects/shots/CameraShutterClick-SoundBible-228518582.wav");
    this->soundCameraShot.setBuffer(this->bufferCameraShot);
    this->menuTitle = new Menu();
    this->menu = true;
    level1 = NULL;
    this->window->create(sf::VideoMode(1024,768), "MetalZombie");
    //this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
    this->window->setMouseCursorVisible(false);
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
    while (this->window->pollEvent(event)) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100) {
            if(menuTitle->getOption() > 0) {
                menuTitle->playSelect();
                menuTitle->setOption(menuTitle->getOption()-1);
                menuTitle->getOptionIcon()->getSprite()->setPosition(menuTitle->getOptionIcon()->getSprite()->getPosition().x, menuTitle->getOptionIcon()->getSprite()->getPosition().y - 100.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100) {
            if(menuTitle->getOption() < 1) {
                menuTitle->playSelect();
                menuTitle->setOption(menuTitle->getOption()+1);
                menuTitle->getOptionIcon()->getSprite()->setPosition(menuTitle->getOptionIcon()->getSprite()->getPosition().x, menuTitle->getOptionIcon()->getSprite()->getPosition().y + 100.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
            switch(menuTitle->getOption()) {
            case 0:
                this->menuTitle->playStart();
                level1 = new Level((char*)"res/sounds/music/level1.ogg");
                this->level1->getPlayer()->setCamera(this->window->getDefaultView());
                this->menu = false;
                delete menuTitle;
                while (this->window->isOpen()) {
                    startGame();
                }
                break;
            default:
                this->window->close();
                break;
            }
        }

    }
    if(this->menu) {
        this->window->draw(menuTitle->getTextTitle());
        this->window->draw(menuTitle->getTextStart());
        this->window->draw(menuTitle->getTextExit());
        this->window->draw(*menuTitle->getOptionIcon()->getSprite());
        this->window->display();
        this->window->clear();
    }
}

void Game::startGame() {
    //--------------------------------------------------------------------
    //-------------------------Player control-----------------------------
    //--------------------------------------------------------------------

    //Needed to do all animations
    sf::Time frame_time;
    //If the player is not moving, then the sprite will draw like standing
    if((!this->level1->getPlayer()->ismovingLeft() && !this->level1->getPlayer()->ismovingRight()) && this->level1->getPlayer()->isLife()) {
        this->level1->getPlayer()->moveRemain();
    }

    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->window->close();
        }
        //Take a screenshot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            this->takeScreenshot();
        }
    }


    if(((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && !this->level1->getPlayer()->isAtacking())) {
        if(this->level1->getPlayer()->isLife()) {
            this->level1->getPlayer()->attack();
        } else {
            if(this->level1->getPlayer()->getLives() > 0) {
                this->level1->getPlayer()->setCamera(this->window->getDefaultView());
                this->level1->restart();
            }
        }
    }

    // Adjust vertical speed
    this->level1->verticalSpeed(this->level1->getPlayer(), 10.f);

    // ResetVelX
    this->level1->getPlayer()->setVelX(0.f);

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->level1->getPlayer()->isLife()) {
        this->level1->getPlayer()->moveRight();
        this->level1->moveUI(window);
    } else {
        this->level1->getPlayer()->setmovingRight(false);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && this->level1->getPlayer()->isLife()) {
        this->level1->getPlayer()->moveLeft();
        this->level1->getPlayer()->getPosWindowX(window);
    } else {
        this->level1->getPlayer()->setmovingLeft(false);
    }

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  && this->level1->getPlayer()->isEndJumping() && this->level1->getPlayer()->isLife()) {
        this->level1->getPlayer()->jump();
    }

    frame_time = frameClock.restart();

    //Move the player
    this->level1->getPlayer()->getSprite()->setPosition(this->level1->getPlayer()->getSprite()->getPosition().x + this->level1->getPlayer()->getVelX() * frame_time.asSeconds(),
            this->level1->getPlayer()->getSprite()->getPosition().y + this->level1->getPlayer()->getVelY() * frame_time.asSeconds());

    //Collisions
    for(unsigned int i = 0; i < (sizeof(this->level1->blocks)/sizeof(this->level1->blocks[i])); i++) {
        if(this->level1->blocks[i]->getSprite()->getGlobalBounds().intersects(this->level1->getPlayer()->getSprite()->getGlobalBounds())) {
            this->level1->getPlayer()->getSprite()->setPosition(this->level1->getPlayer()->getSprite()->getPosition().x,
                    this->level1->blocks[i]->getSprite()->getPosition().y - (this->level1->getPlayer()->getSprite()->getOrigin().y));
            this->level1->getPlayer()->setEndJumping(true);
            this->level1->getPlayer()->setJumping(false);
        }
    }
    if(this->level1->getPlayer()->isJumping()) {
        this->level1->getPlayer()->setEndJumping(false);
    }

    //--------------------------------------------------------------------
    //-------------------------Enemy IA-----------------------------------
    //--------------------------------------------------------------------
    for(unsigned int j = 0; j < (sizeof(this->level1->zombies)/sizeof(this->level1->zombies[j])); j++) {
        // Adjust vertical speed
        this->level1->verticalSpeed(this->level1->zombies[j], 10.f);

        if(this->level1->zombies[j]->isLife()) {
            if(this->level1->getPlayer()->isLife() && (this->level1->zombies[j]->getSprite()->getPosition().x - 40 <= this->level1->getPlayer()->getSprite()->getPosition().x && this->level1->zombies[j]->getSprite()->getPosition().x > this->level1->getPlayer()->getSprite()->getPosition().x) && (this->level1->zombies[j]->getSprite()->getPosition().y <= this->level1->getPlayer()->getSprite()->getPosition().y)) {
                this->level1->zombies[j]->attack(this->level1->getPlayer());
            } else {
                this->level1->zombies[j]->moveLeft();
            }
        }
        this->level1->zombies[j]->getSprite()->setPosition(this->level1->zombies[j]->getSprite()->getPosition().x + this->level1->zombies[j]->getVelX() * frame_time.asSeconds(),
                this->level1->zombies[j]->getSprite()->getPosition().y + this->level1->zombies[j]->getVelY() * frame_time.asSeconds());
        //Collisions
        for(unsigned int i = 0; i < (sizeof(this->level1->blocks)/sizeof(this->level1->blocks[i])); i++) {
            if(this->level1->blocks[i]->getSprite()->getGlobalBounds().intersects(this->level1->zombies[j]->getSprite()->getGlobalBounds())) {
                this->level1->zombies[j]->getSprite()->setPosition(this->level1->zombies[j]->getSprite()->getPosition().x,
                        this->level1->blocks[i]->getSprite()->getPosition().y - (this->level1->zombies[j]->getSprite()->getOrigin().y));
                this->level1->zombies[j]->setEndJumping(true);
                this->level1->zombies[j]->setJumping(false);
            }
        }

        if(this->level1->zombies[j]->isJumping()) {
            this->level1->zombies[j]->setEndJumping(false);
        }
    }

    if(this->level1->getPlayer()->isAtacking()) {
        if(this->level1->getPlayer()->getShot()->isShot()) {
            if(this->level1->getPlayer()->isLookingRight()) {
                this->level1->getPlayer()->getShot()->setDirectionRight(true);
            } else {
                this->level1->getPlayer()->getShot()->setDirectionRight(false);
            }
            this->level1->getPlayer()->getShot()->setShot(false);
        }
        //Collisions with the shot
        //Windows
        if((this->level1->getPlayer()->getShot()->getPosWindowX(window) > this->window->getSize().x || this->level1->getPlayer()->getShot()->getPosWindowX(window) < 0)) {
            this->level1->getPlayer()->setAttacking(false);
            this->level1->getPlayer()->getShot()->endShot();
            //Zombies
        } else {
            for(unsigned int i = 0; i < (sizeof(this->level1->zombies)/sizeof(this->level1->zombies[i])); i++) {
                //Condition to kill the zombie if you are looking left or right and Y position of the shot
                if(this->level1->zombies[i]->isLife() && this->level1->zombies[i]->getSprite()->getGlobalBounds().intersects(this->level1->getPlayer()->getShot()->getSprite()->getGlobalBounds())) {
                    this->level1->getPlayer()->setAttacking(false);
                    this->level1->zombies[i]->die();
                    this->level1->getPlayer()->getShot()->endShot();
                    this->level1->setContZombies(this->level1->getContZombies() + 1);
                } else {
                    this->level1->getPlayer()->getShot()->moveShot(this->level1->getPlayer()->getShot()->isDirectionRight());
                    this->level1->getPlayer()->getShot()->getSprite()->setPosition(this->level1->getPlayer()->getShot()->getSprite()->getPosition().x + this->level1->getPlayer()->getShot()->getVelX() * frame_time.asSeconds(),
                            this->level1->getPlayer()->getShot()->getSprite()->getPosition().y);
                }
            }
        }
    }

    this->window->clear(sf::Color(52,28,27));
    this->window->setView(this->level1->getPlayer()->getCamera());

    //Taking fps
    float fps = 1.f / frame_time.asSeconds();
    lastTimeFPS = frame_time.asSeconds();

    //--------------------------------------------------------------------
    //-------------------------Draw Everything-----------------------------------
    //--------------------------------------------------------------------
    //Draw skies
    for(unsigned int i = 0; i<(sizeof(this->level1->skies)/sizeof(this->level1->skies[i])); i++) {
        this->window->draw(*this->level1->skies[i]->getSprite());
    }
    //Draw builders
    for(unsigned int i = 0; i<(sizeof(this->level1->builders)/sizeof(this->level1->builders[i])); i++) {
        this->window->draw(*this->level1->builders[i]->getSprite());
    }
    //Draw IU
    if(this->level1->getPlayer()->getLives() <= 0 || this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
        if(this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
            this->level1->getPlayer()->moveRight();
        }
        this->window->draw(this->level1->getTextGameOver());
    }
    this->window->draw(this->level1->getTextTime());
    this->window->draw(*this->level1->getLivesFace()->getSprite());
    this->window->draw(this->level1->getTextLives());
    this->window->draw(*this->level1->getZombiesFace()->getSprite());
    this->window->draw(this->level1->getTextZombies());
    //Draw the blocks
    for(unsigned int i = 0; i<(sizeof(this->level1->blocks)/sizeof(this->level1->blocks[i])); i++) {
        this->window->draw(*this->level1->blocks[i]->getSprite());
    }
    //Draw soldiers friends
    for(unsigned int i = 0; i<(sizeof(this->level1->soldiers)/sizeof(this->level1->soldiers[i])); i++) {
        this->window->draw(*this->level1->soldiers[i]->getSprite());
    }
    //Draw shot
    this->window->draw(*(this->level1->getPlayer()->getShot()->getSprite()));
    //Draw the player
    this->level1->getPlayer()->animator.update(frame_time);
    this->level1->getPlayer()->animator.animate(*this->level1->getPlayer()->getSprite());
    this->window->draw(*this->level1->getPlayer()->getSprite());

    //Draw enemys
    for(unsigned int j = 0; j < (sizeof(this->level1->zombies)/sizeof(this->level1->zombies[j])); j++) {
        this->level1->zombies[j]->animator.update(frame_time);
        this->level1->zombies[j]->animator.animate(*this->level1->zombies[j]->getSprite());
        this->window->draw(*this->level1->zombies[j]->getSprite());
    }
    this->window->display();
}

void Game::takeScreenshot() {
    this->soundCameraShot.play();
    sf::Image Screen = this->window->capture();
    time_t tSac = time(NULL);
    struct tm* pt1 = localtime(&tSac);
    std::stringstream filename;
    //screenshot with the actually time and date
    filename << "screenshots/MetalZombie-" << pt1->tm_mday << "_" << pt1->tm_mon+1 << "_" << pt1->tm_year+1900 << "_" << pt1->tm_hour << "_" << pt1->tm_min << "_"<< pt1->tm_sec << ".jpg";
    Screen.saveToFile(filename.str());
}
