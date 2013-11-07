#include "../include/Game.h"


Game::Game() {
    srand(time(NULL));
    window = new sf::RenderWindow();
    this->bufferCameraShot.loadFromFile((char*)"res/sounds/effects/shots/CameraShutterClick-SoundBible-228518582.wav");
    this->soundCameraShot.setBuffer(this->bufferCameraShot);
    this->menu = true;
    this->level = false;
    this->playedSoundIntro = false;
    level1 = NULL;
    this->window->create(sf::VideoMode::getDesktopMode(), "MetalZombie", sf::Style::Fullscreen);
    this->menuTitle = new Menu(this->window->getSize().x, this->window->getSize().y);
    //this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
    this->window->setMouseCursorVisible(false);
    this->frameClock.restart();

    startMenu();
}

Game::~Game() {
    delete window;
    //If the menu igetPosition().xs true, delete them
    if(this->menu) {
        delete this->menuTitle;
        delete level1;
    }
}

void Game::startMenu() {
    while (this->window->isOpen() && this->menu) {
        while (this->window->pollEvent(this->event)) {
            if (this->event.type == sf::Event::Closed) {
                this->window->close();
            }
            if(this->frameClock.getElapsedTime().asSeconds() >= 6.f) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if(this->menuTitle->getOption() > 0) {
                        this->menuTitle->playSelect();
                        this->menuTitle->setOption(this->menuTitle->getOption()-1);
                        this->menuTitle->getOptionIcon()->getSprite()->setPosition(this->menuTitle->getOptionIcon()->getSprite()->getPosition().x, this->menuTitle->getOptionIcon()->getSprite()->getPosition().y - 80.f);
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if(this->menuTitle->getOption() < 1) {
                        this->menuTitle->playSelect();
                        this->menuTitle->setOption(this->menuTitle->getOption()+1);
                        this->menuTitle->getOptionIcon()->getSprite()->setPosition(this->menuTitle->getOptionIcon()->getSprite()->getPosition().x, this->menuTitle->getOptionIcon()->getSprite()->getPosition().y + 80.f);
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
                    switch(this->menuTitle->getOption()) {
                    case 0:
                        this->menuTitle->playStart();
                        level1 = new Level((char*)"res/sounds/music/level1.ogg",this->window->getSize().x, this->window->getSize().y);
                        this->level = true;
                        this->level1->getPlayer()->setCamera(this->window->getDefaultView());
                        this->menu = false;
                        delete this->menuTitle;
                        this->frameClock.restart();
                        startGame();
                        break;
                    default:
                        this->window->close();
                        break;
                    }
                }
            }
        }
        if(this->menu) {
            if(this->frameClock.getElapsedTime().asSeconds() <= 3.f) {
                this->window->draw(*this->menuTitle->getIntroLogo()->getSprite());
            } else if(this->frameClock.getElapsedTime().asSeconds() <= 6.f) {
                this->window->draw(*this->menuTitle->getIntroLogoCC()->getSprite());
            } else {
                if(!playedSoundIntro) {
                    this->menuTitle->playIntroMenu();
                    this->playedSoundIntro = true;
                }
                this->window->draw(this->menuTitle->getTextTitle());
                this->window->draw(this->menuTitle->getTextStart());
                this->window->draw(this->menuTitle->getTextExit());
                this->window->draw(*this->menuTitle->getOptionIcon()->getSprite());
            }
            this->window->display();
            this->window->clear();
        }
    }
}

void Game::startGame() {
    while (this->window->isOpen() && this->level) {
        //Needed to do all animations
        sf::Time frame_time;
        //--------------------------------------------------------------------
        //-------------------------Player control-----------------------------
        //--------------------------------------------------------------------
        while (this->window->pollEvent(this->event)) {
            if (this->event.type == sf::Event::Closed) {
                this->window->close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0,2)) {
                if(!this->level1->isLevelPause()) {
                    this->level1->pauseLevel();
                }
            }
            //Take a screenshot
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) ||sf::Joystick::isButtonPressed(0,1)) {
                this->takeScreenshot();
            }
            //sf::Event::joystickConnect
        }
        if(sf::Joystick::isConnected(0)) {
            this->level1->getJoystickImage()->changeTexture((char*)"res/images/IU/joystick.png");
        } else {
            this->level1->getJoystickImage()->changeTexture((char*)"res/images/IU/no_joystick.png");
        }

        //If the player is not moving, then the sprite will draw like standing
        if((!this->level1->getPlayer()->ismovingLeft() && !this->level1->getPlayer()->ismovingRight()) && this->level1->getPlayer()->isLife()) {
            this->level1->getPlayer()->moveRemain();
        }

        if(((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && !this->level1->getPlayer()->isAtacking())) {
            if(this->level1->getPlayer()->isLife()) {
                this->level1->getPlayer()->attack();
            } else {
                if(this->level1->getPlayer()->getLives() > 0) {
                    this->level1->getPlayer()->setCamera(this->window->getDefaultView());
                    this->level1->restart(this->window->getSize().x, this->window->getSize().y);
                }
            }
        }
        frame_time = this->frameClock.restart();
        if(this->level1->isLevelPause()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if(this->level1->getPauseMenu()->getOption() > 0) {
                    this->level1->getPauseMenu()->playSelect();
                    this->level1->getPauseMenu()->setOption(this->level1->getPauseMenu()->getOption()-1);
                    this->level1->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(this->level1->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, this->level1->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y - 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if(this->level1->getPauseMenu()->getOption() < 1) {
                    this->level1->getPauseMenu()->playSelect();
                    this->level1->getPauseMenu()->setOption(this->level1->getPauseMenu()->getOption()+1);
                    this->level1->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(this->level1->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, this->level1->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y + 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
                switch(this->level1->getPauseMenu()->getOption()) {
                case 0:
                    this->level1->resumeLevel();
                    break;
                default:
                    this->level = false;
                    this->window->close();
                    break;
                }
            }
        } else {
            // Adjust vertical speed
            this->level1->verticalSpeed(this->level1->getPlayer(), 10.f);

            // ResetVelX
            this->level1->getPlayer()->setVelX(0.f);
            if(this->level1->getPlayer()->getVelY() >= 0) {
                this->level1->getPlayer()->setFalling(true);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && this->level1->getPlayer()->isLife()) {
                this->level1->getPlayer()->moveRight();
                this->level1->moveUI(this->window);
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


            //Move the player
            this->level1->getPlayer()->getSprite()->setPosition(this->level1->getPlayer()->getSprite()->getPosition().x + this->level1->getPlayer()->getVelX() * frame_time.asSeconds(),
                    this->level1->getPlayer()->getSprite()->getPosition().y + this->level1->getPlayer()->getVelY() * frame_time.asSeconds());

            //Collisions
            this->level1->blockCollision(this->level1->getPlayer());

            if(this->level1->getPlayer()->isJumping() && this->level1->getPlayer()->isLife()) {
                this->level1->getPlayer()->setEndJumping(false);
                for(unsigned int i = 0; i < (sizeof(this->level1->zombies)/sizeof(this->level1->zombies[i])); i++) {
                    if(this->level1->zombies[i]->getSprite()->getGlobalBounds().intersects(this->level1->getPlayer()->getSprite()->getGlobalBounds()) && this->level1->getPlayer()->isFalling() && this->level1->zombies[i]->isLife()) {
                        this->level1->getPlayer()->jump();
                        this->level1->zombies[i]->die();
                        this->level1->setContZombies(this->level1->getContZombies() + 1);
                    }
                }
            }

            //Player fall
            if(this->level1->getPlayer()->getSprite()->getPosition().y >= window->getSize().y && this->level1->getPlayer()->isLife()) {
                this->level1->getPlayer()->die();
            }

            //--------------------------------------------------------------------
            //-------------------------Enemy IA-----------------------------------
            //--------------------------------------------------------------------
            for(unsigned int j = 0; j < (sizeof(this->level1->zombies)/sizeof(this->level1->zombies[j])); j++) {
                // Adjust vertical speed
                this->level1->verticalSpeed(this->level1->zombies[j], 10.f);
                if(this->level1->zombies[j]->isLife()) {
                    if(this->level1->getPlayer()->isLife() && this->level1->zombies[j]->getSprite()->getGlobalBounds().intersects(this->level1->getPlayer()->getSprite()->getGlobalBounds())) {
                        this->level1->zombies[j]->attack(this->level1->getPlayer());
                    } else {
                        if((this->level1->getPlayer()->getSprite()->getPosition().x - this->level1->zombies[j]->getSprite()->getPosition().x >= -150.f) &&
                                (this->level1->getPlayer()->getSprite()->getPosition().x - this->level1->zombies[j]->getSprite()->getPosition().x <= -5.f)) {
                            this->level1->zombies[j]->moveLeft();
                        } else if((this->level1->getPlayer()->getSprite()->getPosition().x - this->level1->zombies[j]->getSprite()->getPosition().x <= 150.f)&&
                                  (this->level1->getPlayer()->getSprite()->getPosition().x - this->level1->zombies[j]->getSprite()->getPosition().x >= 5.f)) {
                            this->level1->zombies[j]->moveRight();
                        } else {
                            if(this->level1->zombies[j]->getRandomMove() >= 2) {
                                this->level1->zombies[j]->moveLeft();
                            } else if(this->level1->zombies[j]->getRandomMove() == 1) {
                                this->level1->zombies[j]->moveRight();
                            } else {
                                this->level1->zombies[j]->moveRemain();
                            }
                            if(this->level1->zombies[j]->getMoveTime().getElapsedTime().asSeconds() >= 3) {
                                this->level1->zombies[j]->setRandomeMove(rand()%3);
                                this->level1->zombies[j]->resetMoveTime();
                            }
                        }
                    }
                }
                this->level1->zombies[j]->getSprite()->setPosition(this->level1->zombies[j]->getSprite()->getPosition().x + this->level1->zombies[j]->getVelX() * frame_time.asSeconds(),
                        this->level1->zombies[j]->getSprite()->getPosition().y + this->level1->zombies[j]->getVelY() * frame_time.asSeconds());
                //Collisions
                this->level1->blockCollision(this->level1->zombies[j]);

                if(this->level1->zombies[j]->isJumping()) {
                    this->level1->zombies[j]->setEndJumping(false);
                }

                if(this->level1->zombies[j]->getSprite()->getPosition().y <= 0) {
                    this->level1->zombies[j]->die();
                }
            }

            //--------------------------------------------------------------------
            //-------------------------Shot-----------------------------------
            //--------------------------------------------------------------------
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
                        if(this->level1->getPlayer()->getShot()->collisionCharacter(this->level1->zombies[i])) {
                            this->level1->getPlayer()->setAttacking(false);
                            this->level1->setContZombies(this->level1->getContZombies() + 1);
                        } else {
                            this->level1->getPlayer()->getShot()->getSprite()->setPosition(this->level1->getPlayer()->getShot()->getSprite()->getPosition().x + this->level1->getPlayer()->getShot()->getVelX() * frame_time.asSeconds(),
                                    this->level1->getPlayer()->getShot()->getSprite()->getPosition().y);
                        }
                    }
                }
            }
        }
        this->window->clear(sf::Color(52,28,27));
        this->window->setView(this->level1->getPlayer()->getCamera());

        //Taking fps
        this->level1->setFPS(1.f / frame_time.asSeconds());

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

        //Draw IU
        //If the game is paused, draw the menu
        if(this->level1->isLevelPause()) {
            this->window->draw(this->level1->getPauseMenu()->getTextStart());
            this->window->draw(this->level1->getPauseMenu()->getTextExit());
            this->window->draw(*this->level1->getPauseMenu()->getOptionIcon()->getSprite());
        }
        this->window->draw(this->level1->getTextTime());
        this->window->draw(*this->level1->getLivesFace()->getSprite());
        this->window->draw(this->level1->getTextLives());
        this->window->draw(*this->level1->getZombiesFace()->getSprite());
        this->window->draw(this->level1->getTextZombies());
        this->window->draw(this->level1->getTextFPS());
        this->window->draw(*this->level1->getJoystickImage()->getSprite());
        if(this->level1->getPlayer()->getLives() <= 0 || this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
            if(this->level1->getPlayer()->getSprite()->getPosition().x >= 9900) {
                this->level1->getPlayer()->moveRight();
            }
            this->window->draw(this->level1->getTextGameOver());
        }
        this->window->display();
    }
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
