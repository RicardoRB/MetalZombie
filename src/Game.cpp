#include "../include/Game.h"


Game::Game() {
    srand(time(NULL));
    window = new sf::RenderWindow();
    this->bufferCameraShot.loadFromFile((char*)"res/sounds/effects/shots/CameraShutterClick-SoundBible-228518582.wav");
    this->soundCameraShot.setBuffer(this->bufferCameraShot);
    this->menu = true;
    this->level = false;
    this->playedSoundIntro = false;
    this->window->create(sf::VideoMode::getDesktopMode(), "MetalZombie", sf::Style::Fullscreen);
    this->menuTitle = new Menu(this->window->getSize().x, this->window->getSize().y);
    this->window->setVerticalSyncEnabled(true);
    this->window->setMouseCursorVisible(false);
    this->frameClock.restart();
    startMenu();
}

Game::~Game() {
    delete window;
    delete this->menuTitle;
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
                    case 0: {
                        this->menuTitle->playStart();
                        //Level *level1 = new Level((char*)"res/sounds/music/level1.ogg",this->window->getSize().x, this->window->getSize().y,35,320,20,40,10);
                        LevelBoss *level1 = new LevelBoss((char*)"res/images/backgrounds/level1/boss.png",(char*)"res/sounds/music/level1.ogg",this->window->getSize().x, this->window->getSize().y,18,32);
                        this->level = true;
                        level1->getPlayer()->setCamera(this->window->getDefaultView());
                        this->menu = false;
                        this->frameClock.restart();
                        startLevelBoss(level1);
                        //startLevel(level1);
                        break;
                    }
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

void Game::startLevel(Level* _level) {
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
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0,2)) {
            if(!_level->isLevelPause()) {
                _level->pauseLevel();
            }
        }
        if(sf::Joystick::isConnected(0)) {
            _level->getJoystickImage()->changeTexture((char*)"res/images/IU/joystick.png");
        } else {
            _level->getJoystickImage()->changeTexture((char*)"res/images/IU/no_joystick.png");
        }
        //Take a screenshot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) ||sf::Joystick::isButtonPressed(0,1)) {
            this->takeScreenshot();
        }

        //If the player is not moving, then the sprite will draw like standing
        if((!_level->getPlayer()->ismovingLeft() && !_level->getPlayer()->ismovingRight()) && _level->getPlayer()->isLife()) {
            _level->getPlayer()->moveRemain();
        }

        if(((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && !_level->getPlayer()->isAtacking())) {
            if(_level->getPlayer()->isLife()) {
                _level->getPlayer()->attack();
            } else {
                if(_level->getPlayer()->getLives() > 0) {
                    _level->getPlayer()->setCamera(this->window->getDefaultView());
                    _level->restart(this->window->getSize().x, this->window->getSize().y);
                }
            }
        }
        frame_time = this->frameClock.restart();
        if(_level->isLevelPause()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if(_level->getPauseMenu()->getOption() > 0) {
                    _level->getPauseMenu()->playSelect();
                    _level->getPauseMenu()->setOption(_level->getPauseMenu()->getOption()-1);
                    _level->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(_level->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, _level->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y - 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if(_level->getPauseMenu()->getOption() < 1) {
                    _level->getPauseMenu()->playSelect();
                    _level->getPauseMenu()->setOption(_level->getPauseMenu()->getOption()+1);
                    _level->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(_level->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, _level->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y + 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
                switch(_level->getPauseMenu()->getOption()) {
                case 0:
                    _level->resumeLevel();
                    break;
                default:
                    this->level = false;
                    this->menu = true;
                    this->window->setView(this->window->getDefaultView());
                    this->startMenu();
                    break;
                }
            }
        } else {
            // Adjust vertical speed
            _level->verticalSpeed(_level->getPlayer(), 10.f);

            // ResetVelX
            _level->getPlayer()->setVelX(0.f);
            if(_level->getPlayer()->getVelY() >= 0) {
                _level->getPlayer()->setFalling(true);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && _level->getPlayer()->isLife()) {
                _level->getPlayer()->moveRight();
                _level->moveUI(this->window);
            } else {
                _level->getPlayer()->setmovingRight(false);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && _level->getPlayer()->isLife()) {
                _level->getPlayer()->moveLeft();
                _level->getPlayer()->getPosWindowX(window);
            } else {
                _level->getPlayer()->setmovingLeft(false);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  && _level->getPlayer()->isEndJumping() && _level->getPlayer()->isLife()) {
                _level->getPlayer()->jump();
            }


            //Move the player
            _level->getPlayer()->getSprite()->setPosition(_level->getPlayer()->getSprite()->getPosition().x + _level->getPlayer()->getVelX() * frame_time.asSeconds(),
                    _level->getPlayer()->getSprite()->getPosition().y + _level->getPlayer()->getVelY() * frame_time.asSeconds());

            //Collisions
            _level->blockCollision(_level->getPlayer(),_level->blocks);

            if(_level->getPlayer()->isJumping() && _level->getPlayer()->isLife()) {
                _level->getPlayer()->setEndJumping(false);
                for(unsigned int i = 0; i < _level->zombies.size(); i++) {
                    if(_level->zombies.at(i)->getSprite()->getGlobalBounds().intersects(_level->getPlayer()->getSprite()->getGlobalBounds()) && _level->getPlayer()->isFalling() && _level->zombies.at(i)->isLife()) {
                        _level->getPlayer()->jump();
                        if(_level->zombies.at(i)->getLives() <= 0) {
                            _level->zombies.at(i)->die();
                            _level->setContZombies(_level->getContZombies() + 1);
                        } else {
                            _level->zombies.at(i)->setLives(_level->zombies.at(i)->getLives() - 1);
                        }
                    }
                }
            }


            //Player fall
            if(_level->getPlayer()->getSprite()->getPosition().y >= window->getSize().y && _level->getPlayer()->isLife()) {
                _level->getPlayer()->die();
            }

            //--------------------------------------------------------------------
            //-------------------------Enemy IA-----------------------------------
            //--------------------------------------------------------------------
            //--------------------------------------------------------------------
            //-------------------------Zombies-----------------------------------
            //--------------------------------------------------------------------
            for(unsigned int j = 0; j < _level->zombies.size(); j++) {
                // Adjust vertical speed
                _level->verticalSpeed(_level->zombies.at(j), 10.f);
                if(_level->zombies.at(j)->isLife()) {
                    if(_level->getPlayer()->isLife() && _level->zombies.at(j)->getSprite()->getGlobalBounds().intersects(_level->getPlayer()->getSprite()->getGlobalBounds())) {
                        _level->zombies.at(j)->attack(_level->getPlayer());
                    } else {
                        //Follow the player
                        if((_level->getPlayer()->getSprite()->getPosition().x - _level->zombies.at(j)->getSprite()->getPosition().x >= -150.f) &&
                                (_level->getPlayer()->getSprite()->getPosition().x - _level->zombies.at(j)->getSprite()->getPosition().x <= -5.f) &&
                                (_level->getPlayer()->getSprite()->getPosition().y - _level->zombies.at(j)->getSprite()->getPosition().y < 10 &&
                                 _level->zombies.at(j)->getSprite()->getPosition().y - _level->getPlayer()->getSprite()->getPosition().y < 10)) {
                            _level->zombies.at(j)->moveLeft();
                        } else if((_level->getPlayer()->getSprite()->getPosition().x - _level->zombies.at(j)->getSprite()->getPosition().x <= 150.f)&&
                                  (_level->getPlayer()->getSprite()->getPosition().x - _level->zombies.at(j)->getSprite()->getPosition().x >= 5.f) &&
                                  (_level->getPlayer()->getSprite()->getPosition().y - _level->zombies.at(j)->getSprite()->getPosition().y < 10 &&
                                   _level->zombies.at(j)->getSprite()->getPosition().y - _level->getPlayer()->getSprite()->getPosition().y < 10)) {
                            _level->zombies.at(j)->moveRight();
                        } else {
                            unsigned int blockPosition = _level->zombies.at(j)->getSprite()->getPosition().x / _level->blocks.at(0)->getSprite()->getTexture()->getSize().x;
                            if(blockPosition >= _level->blocks.size()-1 || blockPosition <= 0) {
                                if(_level->zombies.at(j)->ismovingRight()) {
                                    _level->zombies.at(j)->setRandomMove(2);
                                } else {
                                    _level->zombies.at(j)->setRandomMove(1);
                                }
                            } else {
                                if(_level->blocks.at(blockPosition+1)->getSprite()->getPosition().y - _level->zombies.at(j)->getSprite()->getPosition().y < 10 ||
                                        _level->blocks.at(blockPosition-1)->getSprite()->getPosition().y - _level->zombies.at(j)->getSprite()->getPosition().y < 10) {
                                    if(_level->zombies.at(j)->ismovingRight()) {
                                        _level->zombies.at(j)->setRandomMove(2);
                                    } else {
                                        _level->zombies.at(j)->setRandomMove(1);
                                    }
                                }
                            }
                            if(_level->zombies.at(j)->getRandomMove() >= 2) {
                                _level->zombies.at(j)->moveLeft();
                            } else if(_level->zombies.at(j)->getRandomMove() == 1) {
                                _level->zombies.at(j)->moveRight();
                            } else {
                                _level->zombies.at(j)->moveRemain();
                            }
                            if(_level->zombies.at(j)->getMoveTime().getElapsedTime().asSeconds() >= 3) {
                                _level->zombies.at(j)->setRandomMove(rand()%3);
                                _level->zombies.at(j)->resetMoveTime();
                            }
                        }
                    }
                }
                _level->zombies.at(j)->getSprite()->setPosition(_level->zombies.at(j)->getSprite()->getPosition().x + _level->zombies.at(j)->getVelX() * frame_time.asSeconds(),
                        _level->zombies.at(j)->getSprite()->getPosition().y + _level->zombies.at(j)->getVelY() * frame_time.asSeconds());
                //Collisions
                _level->blockCollision(_level->zombies.at(j),_level->blocks);

                if(_level->zombies.at(j)->isJumping()) {
                    _level->zombies.at(j)->setEndJumping(false);
                }
            }

            //--------------------------------------------------------------------
            //-------------------------Shot-----------------------------------
            //--------------------------------------------------------------------
            if(_level->getPlayer()->isAtacking()) {
                if(_level->getPlayer()->getShot()->isShot()) {
                    if(_level->getPlayer()->isLookingRight()) {
                        _level->getPlayer()->getShot()->setDirectionRight(true);
                    } else {
                        _level->getPlayer()->getShot()->setDirectionRight(false);
                    }
                    _level->getPlayer()->getShot()->setShot(false);
                }
                //Collisions with the shot
                //Windows
                if((_level->getPlayer()->getShot()->getPosWindowX(window) > this->window->getSize().x || _level->getPlayer()->getShot()->getPosWindowX(window) < 0)) {
                    _level->getPlayer()->setAttacking(false);
                    _level->getPlayer()->getShot()->endShot();
                    //Zombies
                } else {
                    for(unsigned int i = 0; i < _level->zombies.size(); i++) {
                        if(_level->getPlayer()->getShot()->collisionCharacter(_level->zombies.at(i))) {
                            if(_level->zombies.at(i)->getLives() <= 0) {
                                _level->zombies.at(i)->die();
                                _level->setContZombies(_level->getContZombies() + 1);
                            } else {
                                _level->zombies.at(i)->setLives(_level->zombies.at(i)->getLives() - 1);
                            }
                            _level->getPlayer()->setAttacking(false);
                            _level->getPlayer()->getShot()->endShot();
                        } else {
                            _level->getPlayer()->getShot()->moveShot(_level->getPlayer()->getShot()->isDirectionRight());
                        }
                    }
                }
            }
            _level->getPlayer()->getShot()->getSprite()->setPosition(_level->getPlayer()->getShot()->getSprite()->getPosition().x + _level->getPlayer()->getShot()->getVelX() * frame_time.asSeconds(),
                    _level->getPlayer()->getShot()->getSprite()->getPosition().y);
        }
        this->window->clear(sf::Color(52,28,27));
        this->window->setView(_level->getPlayer()->getCamera());

        //Taking fps
        _level->setFPS(1.f / frame_time.asSeconds());

        //--------------------------------------------------------------------
        //-------------------------Draw Everything-----------------------------------
        //--------------------------------------------------------------------
        //Draw skies
        for(unsigned int i = 0; i<_level->skies.size(); i++) {
            this->window->draw(*_level->skies.at(i)->getSprite());
        }
        //Draw builders
        for(unsigned int i = 0; i<_level->builders.size(); i++) {
            this->window->draw(*_level->builders.at(i)->getSprite());
        }
        //Draw the blocks
        for(unsigned int i = 0; i<_level->blocks.size(); i++) {
            this->window->draw(*_level->blocks.at(i)->getSprite());
        }
        //Draw the platforms
        for(unsigned int i = 0; i<_level->platforms.size(); i++) {
            this->window->draw(*_level->platforms.at(i)->getSprite());
        }
        //Draw soldiers friends
        for(unsigned int i = 0; i<_level->soldiers.size(); i++) {
            this->window->draw(*_level->soldiers.at(i)->getSprite());
        }
        //Draw shot
        this->window->draw(*(_level->getPlayer()->getShot()->getSprite()));
        //Draw the player
        _level->getPlayer()->animator.update(frame_time);
        _level->getPlayer()->animator.animate(*_level->getPlayer()->getSprite());
        this->window->draw(*_level->getPlayer()->getSprite());

        //Draw enemys
        for(unsigned int j = 0; j < _level->zombies.size(); j++) {
            _level->zombies.at(j)->animator.update(frame_time);
            _level->zombies.at(j)->animator.animate(*_level->zombies.at(j)->getSprite());
            this->window->draw(*_level->zombies.at(j)->getSprite());
        }

        //Draw IU
        //If the game is paused, draw the menu
        if(_level->isLevelPause()) {
            this->window->draw(_level->getPauseMenu()->getTextStart());
            this->window->draw(_level->getPauseMenu()->getTextExit());
            this->window->draw(*_level->getPauseMenu()->getOptionIcon()->getSprite());
        }
        this->window->draw(_level->getTextTime());
        this->window->draw(*_level->getLivesFace()->getSprite());
        this->window->draw(_level->getTextLives());
        this->window->draw(*_level->getZombiesFace()->getSprite());
        this->window->draw(_level->getTextZombies());
        this->window->draw(_level->getTextFPS());
        this->window->draw(*_level->getJoystickImage()->getSprite());
        //EndLevel
        //The screen will not move if there is not more blocks
        if(_level->getPlayer()->getSprite()->getPosition().x >= (_level->blocks.size() * _level->blocks.at(0)->getSprite()->getTexture()->getSize().x) - (this->window->getSize().x/2)) {
            _level->getPlayer()->setEndLevel(true);
        }
        //EndGame
        if(_level->getPlayer()->getLives() <= 0) {
            this->window->draw(_level->getTextGameOver());
        }
        this->window->display();
    }
}

void Game::startLevelBoss(LevelBoss* _levelBoss) {
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
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0,2)) {
            if(!_levelBoss->isLevelPause()) {
                _levelBoss->pauseLevel();
            }
        }
        if(sf::Joystick::isConnected(0)) {
            _levelBoss->getJoystickImage()->changeTexture((char*)"res/images/IU/joystick.png");
        } else {
            _levelBoss->getJoystickImage()->changeTexture((char*)"res/images/IU/no_joystick.png");
        }
        //Take a screenshot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) ||sf::Joystick::isButtonPressed(0,1)) {
            this->takeScreenshot();
        }

        //If the player is not moving, then the sprite will draw like standing
        if((!_levelBoss->getPlayer()->ismovingLeft() && !_levelBoss->getPlayer()->ismovingRight()) && _levelBoss->getPlayer()->isLife()) {
            _levelBoss->getPlayer()->moveRemain();
        }

        if(((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) && !_levelBoss->getPlayer()->isAtacking())) {
            if(_levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->attack();
            } else {
                if(_levelBoss->getPlayer()->getLives() > 0) {
                    _levelBoss->getPlayer()->setCamera(this->window->getDefaultView());
                    _levelBoss->restart(this->window->getSize().x, this->window->getSize().y);
                }
            }
        }
        frame_time = this->frameClock.restart();
        if(_levelBoss->isLevelPause()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if(_levelBoss->getPauseMenu()->getOption() > 0) {
                    _levelBoss->getPauseMenu()->playSelect();
                    _levelBoss->getPauseMenu()->setOption(_levelBoss->getPauseMenu()->getOption()-1);
                    _levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(_levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, _levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y - 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if(_levelBoss->getPauseMenu()->getOption() < 1) {
                    _levelBoss->getPauseMenu()->playSelect();
                    _levelBoss->getPauseMenu()->setOption(_levelBoss->getPauseMenu()->getOption()+1);
                    _levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->setPosition(_levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().x, _levelBoss->getPauseMenu()->getOptionIcon()->getSprite()->getPosition().y + 80.f);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0,0)) {
                switch(_levelBoss->getPauseMenu()->getOption()) {
                case 0:
                    _levelBoss->resumeLevel();
                    break;
                default:
                    this->level = false;
                    this->menu = true;
                    this->window->setView(this->window->getDefaultView());
                    this->startMenu();
                    break;
                }
            }
        } else {
            // Adjust vertical speed
            _levelBoss->verticalSpeed(_levelBoss->getPlayer(), 10.f);

            // ResetVelX
            _levelBoss->getPlayer()->setVelX(0.f);
            if(_levelBoss->getPlayer()->getVelY() >= 0) {
                _levelBoss->getPlayer()->setFalling(true);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && _levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->moveRight();
            } else {
                _levelBoss->getPlayer()->setmovingRight(false);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && _levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->moveLeft();
                _levelBoss->getPlayer()->getPosWindowX(window);
            } else {
                _levelBoss->getPlayer()->setmovingLeft(false);
            }

            if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  && _levelBoss->getPlayer()->isEndJumping() && _levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->jump();
            }


            //Move the player
            _levelBoss->getPlayer()->getSprite()->setPosition(_levelBoss->getPlayer()->getSprite()->getPosition().x + _levelBoss->getPlayer()->getVelX() * frame_time.asSeconds(),
                    _levelBoss->getPlayer()->getSprite()->getPosition().y + _levelBoss->getPlayer()->getVelY() * frame_time.asSeconds());

            //Collisions
            _levelBoss->blockCollision(_levelBoss->getPlayer(),_levelBoss->blocks);
            _levelBoss->blockCollision(_levelBoss->getPlayer(),_levelBoss->platforms);

            if(_levelBoss->getPlayer()->isJumping() && _levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->setEndJumping(false);
                for(unsigned int i = 0; i < _levelBoss->zombies.size(); i++) {
                    if(_levelBoss->zombies.at(i)->getSprite()->getGlobalBounds().intersects(_levelBoss->getPlayer()->getSprite()->getGlobalBounds()) && _levelBoss->getPlayer()->isFalling() && _levelBoss->zombies.at(i)->isLife()) {
                        _levelBoss->getPlayer()->jump();
                        if(_levelBoss->zombies.at(i)->getLives() <= 0) {
                            _levelBoss->zombies.at(i)->die();
                            _levelBoss->setContZombies(_levelBoss->getContZombies() + 1);
                            _levelBoss->setDeadZombiesPhase(_levelBoss->getDeadZombiesPhase()+1);
                        } else {
                            _levelBoss->zombies.at(i)->setLives(_levelBoss->zombies.at(i)->getLives() - 1);
                        }
                    }
                }
            }


            //Player fall
            if(_levelBoss->getPlayer()->getSprite()->getPosition().y >= window->getSize().y && _levelBoss->getPlayer()->isLife()) {
                _levelBoss->getPlayer()->die();
            }

            //--------------------------------------------------------------------
            //-------------------------Enemy IA-----------------------------------
            //--------------------------------------------------------------------
            //--------------------------------------------------------------------
            //-------------------------Zombies------------------------------------
            //--------------------------------------------------------------------
            if((_levelBoss->getBoss()->isTube() && _levelBoss->isZombiePhase()) && _levelBoss->getDeadZombiesPhase() == 6) {
                _levelBoss->setDeadZombiesPhase(0);
                _levelBoss->setZombiePhase(false);
                if(_levelBoss->getTimeTube()->isRunning()) {
                    _levelBoss->getTimeTube()->reset();
                    _levelBoss->getTimeTube()->start();
                } else {
                    _levelBoss->getTimeTube()->start();
                }
                _levelBoss->changeTubeSprite();
            }
            for(unsigned int j = ((_levelBoss->getBoss()->getMaxRecoverys() - (_levelBoss->getBoss()->getRecoverys()+1)) * 6); j < ((_levelBoss->getBoss()->getMaxRecoverys() - (_levelBoss->getBoss()->getRecoverys())) * 6); j++) {

                if((_levelBoss->zombies.at(j)->isLife() && _levelBoss->getBoss()->isTube()) && _levelBoss->isFirstBlackScreen()) {
                    // Adjust vertical speed
                    _levelBoss->verticalSpeed(_levelBoss->zombies.at(j), 10.f);
                    if(_levelBoss->getPlayer()->isLife() && _levelBoss->zombies.at(j)->getSprite()->getGlobalBounds().intersects(_levelBoss->getPlayer()->getSprite()->getGlobalBounds())) {
                        _levelBoss->zombies.at(j)->attack(_levelBoss->getPlayer());
                    } else {
                        //Follow the player
                        if((_levelBoss->getPlayer()->getSprite()->getPosition().x - _levelBoss->zombies.at(j)->getSprite()->getPosition().x >= -150.f) &&
                                (_levelBoss->getPlayer()->getSprite()->getPosition().x - _levelBoss->zombies.at(j)->getSprite()->getPosition().x <= -5.f) &&
                                (_levelBoss->getPlayer()->getSprite()->getPosition().y - _levelBoss->zombies.at(j)->getSprite()->getPosition().y < 10 &&
                                 _levelBoss->zombies.at(j)->getSprite()->getPosition().y - _levelBoss->getPlayer()->getSprite()->getPosition().y < 10)) {
                            _levelBoss->zombies.at(j)->moveLeft();
                        } else if((_levelBoss->getPlayer()->getSprite()->getPosition().x - _levelBoss->zombies.at(j)->getSprite()->getPosition().x <= 150.f)&&
                                  (_levelBoss->getPlayer()->getSprite()->getPosition().x - _levelBoss->zombies.at(j)->getSprite()->getPosition().x >= 5.f) &&
                                  (_levelBoss->getPlayer()->getSprite()->getPosition().y - _levelBoss->zombies.at(j)->getSprite()->getPosition().y < 10 &&
                                   _levelBoss->zombies.at(j)->getSprite()->getPosition().y - _levelBoss->getPlayer()->getSprite()->getPosition().y < 10)) {
                            _levelBoss->zombies.at(j)->moveRight();
                        } else {
                            unsigned int blockPosition = _levelBoss->zombies.at(j)->getSprite()->getPosition().x / _levelBoss->blocks.at(0)->getSprite()->getTexture()->getSize().x;
                            if(blockPosition >= _levelBoss->blocks.size()-1 || blockPosition <= 0) {
                                if(_levelBoss->zombies.at(j)->ismovingRight()) {
                                    _levelBoss->zombies.at(j)->setRandomMove(2);
                                } else {
                                    _levelBoss->zombies.at(j)->setRandomMove(1);
                                }
                            } else {
                                if(_levelBoss->blocks.at(blockPosition+1)->getSprite()->getPosition().y - _levelBoss->zombies.at(j)->getSprite()->getPosition().y < 10 ||
                                        _levelBoss->blocks.at(blockPosition-1)->getSprite()->getPosition().y - _levelBoss->zombies.at(j)->getSprite()->getPosition().y < 10) {
                                    if(_levelBoss->zombies.at(j)->ismovingRight()) {
                                        _levelBoss->zombies.at(j)->setRandomMove(2);
                                    } else {
                                        _levelBoss->zombies.at(j)->setRandomMove(1);
                                    }
                                }
                            }
                            if(_levelBoss->zombies.at(j)->getRandomMove() >= 2) {
                                _levelBoss->zombies.at(j)->moveLeft();
                            } else if(_levelBoss->zombies.at(j)->getRandomMove() == 1) {
                                _levelBoss->zombies.at(j)->moveRight();
                            } else {
                                _levelBoss->zombies.at(j)->moveRemain();
                            }
                            if(_levelBoss->zombies.at(j)->getMoveTime().getElapsedTime().asSeconds() >= 3) {
                                _levelBoss->zombies.at(j)->setRandomMove(rand()%3);
                                _levelBoss->zombies.at(j)->resetMoveTime();
                            }
                        }
                    }
                }
                _levelBoss->zombies.at(j)->getSprite()->setPosition(_levelBoss->zombies.at(j)->getSprite()->getPosition().x + _levelBoss->zombies.at(j)->getVelX() * frame_time.asSeconds(),
                        _levelBoss->zombies.at(j)->getSprite()->getPosition().y + _levelBoss->zombies.at(j)->getVelY() * frame_time.asSeconds());
                //Collisions
                _levelBoss->blockCollision(_levelBoss->zombies.at(j),_levelBoss->blocks);

                if(_levelBoss->zombies.at(j)->isJumping()) {
                    _levelBoss->zombies.at(j)->setEndJumping(false);
                }
            }
            //--------------------------------------------------------------------
            //-------------------------Enemy BOSS---------------------------------
            //--------------------------------------------------------------------
            _levelBoss->verticalSpeed(_levelBoss->getBoss(), 10.f);
            if(!_levelBoss->getBoss()->isTube() && _levelBoss->getBoss()->isLife()) {
                if(_levelBoss->getPlayer()->isLife() && _levelBoss->getBoss()->getSprite()->getGlobalBounds().intersects(_levelBoss->getPlayer()->getSprite()->getGlobalBounds())) {
                    _levelBoss->getBoss()->attack(_levelBoss->getPlayer());
                }
                unsigned int blockPosition = _levelBoss->getBoss()->getSprite()->getPosition().x / _levelBoss->blocks.at(0)->getSprite()->getTexture()->getSize().x;
                if(blockPosition >= _levelBoss->blocks.size()-1 || blockPosition <= 0) {
                    if(_levelBoss->getBoss()->ismovingRight()) {
                        _levelBoss->getBoss()->moveLeft();
                    } else {

                        _levelBoss->getBoss()->moveRight();
                    }
                }

                if(_levelBoss->getBoss()->ismovingRight()) {
                    _levelBoss->getBoss()->moveRight();
                } else {
                    _levelBoss->getBoss()->moveLeft();
                }
                if(_levelBoss->getBoss()->getRecoverys() == 2 || _levelBoss->getBoss()->getRecoverys() == 4) {
                    if(_levelBoss->getBoss()->getVelY() >= 0) {
                        _levelBoss->getBoss()->setFalling(true);
                    }
                    if(_levelBoss->getBoss()->isEndJumping()) {
                        _levelBoss->getBoss()->jump();
                    }
                }
            } else {
                _levelBoss->getBoss()->setVelX(0);
                _levelBoss->getBoss()->setFalling(true);
            }
            _levelBoss->getBoss()->getSprite()->setPosition(_levelBoss->getBoss()->getSprite()->getPosition().x + _levelBoss->getBoss()->getVelX() * frame_time.asSeconds(),
                    _levelBoss->getBoss()->getSprite()->getPosition().y + _levelBoss->getBoss()->getVelY() * frame_time.asSeconds());
            _levelBoss->blockCollision(_levelBoss->getBoss(),_levelBoss->blocks);

            //--------------------------------------------------------------------
            //-------------------------Shot-----------------------------------
            //--------------------------------------------------------------------
            if(_levelBoss->getPlayer()->isAtacking()) {
                if(_levelBoss->getPlayer()->getShot()->isShot()) {
                    if(_levelBoss->getPlayer()->isLookingRight()) {
                        _levelBoss->getPlayer()->getShot()->setDirectionRight(true);
                    } else {
                        _levelBoss->getPlayer()->getShot()->setDirectionRight(false);
                    }
                    _levelBoss->getPlayer()->getShot()->setShot(false);
                }
                //Collisions with the shot
                //Windows
                if((_levelBoss->getPlayer()->getShot()->getPosWindowX(window) > this->window->getSize().x || _levelBoss->getPlayer()->getShot()->getPosWindowX(window) < 0)) {
                    _levelBoss->getPlayer()->setAttacking(false);
                    _levelBoss->getPlayer()->getShot()->endShot();
                    //Zombies
                    //Boss
                } else if(_levelBoss->getPlayer()->getShot()->collisionCharacter(_levelBoss->getBoss()) && !_levelBoss->getBoss()->isTube()) {
                    _levelBoss->getBoss()->hit();

                    if(_levelBoss->getBoss()->getLives() <= 0 && _levelBoss->getBoss()->getRecoverys() <= 0) {
                        _levelBoss->getBoss()->die();
                    }
                    if(_levelBoss->getBoss()->getLives() <= 0 && _levelBoss->getBoss()->getRecoverys() > 0) {
                        _levelBoss->setZombiePhase(true);
                        _levelBoss->getBoss()->setRecoverys(_levelBoss->getBoss()->getRecoverys() - 1);
                        if(_levelBoss->getTimeTube()->isRunning()) {
                            _levelBoss->getTimeTube()->reset();
                            _levelBoss->getTimeTube()->start();
                        } else {
                            _levelBoss->getTimeTube()->start();
                        }
                        _levelBoss->setFirstBlackScreen(true);
                        _levelBoss->changeTubeSprite();
                    }
                    _levelBoss->reduceLifeBar();
                    _levelBoss->getPlayer()->setAttacking(false);
                    _levelBoss->getPlayer()->getShot()->endShot();
                } else {
                    for(unsigned int i = 0; i < _levelBoss->zombies.size(); i++) {
                        if(_levelBoss->getPlayer()->getShot()->collisionCharacter(_levelBoss->zombies.at(i))) {
                            if(_levelBoss->zombies.at(i)->getLives() <= 0) {
                                _levelBoss->setDeadZombiesPhase(_levelBoss->getDeadZombiesPhase()+1);
                                _levelBoss->zombies.at(i)->die();
                                _levelBoss->setContZombies(_levelBoss->getContZombies() + 1);
                            } else {
                                _levelBoss->zombies.at(i)->setLives(_levelBoss->zombies.at(i)->getLives() - 1);
                            }
                            _levelBoss->getPlayer()->setAttacking(false);
                            _levelBoss->getPlayer()->getShot()->endShot();
                        }
                    }
                }
                _levelBoss->getPlayer()->getShot()->moveShot(_levelBoss->getPlayer()->getShot()->isDirectionRight());
            }
            _levelBoss->getPlayer()->getShot()->getSprite()->setPosition(_levelBoss->getPlayer()->getShot()->getSprite()->getPosition().x + _levelBoss->getPlayer()->getShot()->getVelX() * frame_time.asSeconds(),
                    _levelBoss->getPlayer()->getShot()->getSprite()->getPosition().y);
        }
        this->window->clear(sf::Color::Black);
        this->window->setView(_levelBoss->getPlayer()->getCamera());

        //Taking fps
        _levelBoss->setFPS(1.f / frame_time.asSeconds());

        //--------------------------------------------------------------------
        //-------------------------Draw Everything----------------------------
        //--------------------------------------------------------------------
        if(((_levelBoss->getClockSeconds() < 5.f || _levelBoss->getClockSeconds() > 6.f) && !_levelBoss->isFirstBlackScreen()) || _levelBoss->getTimeTube()->getElapsedTime().asSeconds() > 1.f) {
            this->window->draw(*_levelBoss->getBackgroundBoss()->getSprite());
            //Draw the blocks
            for(unsigned int i = 0; i<_levelBoss->blocks.size(); i++) {
                this->window->draw(*_levelBoss->blocks.at(i)->getSprite());
            }
            //Draw the platforms
            for(unsigned int i = 0; i<_levelBoss->platforms.size(); i++) {
                this->window->draw(*_levelBoss->platforms.at(i)->getSprite());
            }
            //Draw shot
            this->window->draw(*(_levelBoss->getPlayer()->getShot()->getSprite()));
            //Draw the player
            _levelBoss->getPlayer()->animator.update(frame_time);
            _levelBoss->getPlayer()->animator.animate(*_levelBoss->getPlayer()->getSprite());
            this->window->draw(*_levelBoss->getPlayer()->getSprite());

            //Draw enemys
            for(unsigned int j = ((_levelBoss->getBoss()->getMaxRecoverys() - (_levelBoss->getBoss()->getRecoverys()+1)) * 6); j < ((_levelBoss->getBoss()->getMaxRecoverys() - (_levelBoss->getBoss()->getRecoverys())) * 6); j++) {
                _levelBoss->zombies.at(j)->animator.update(frame_time);
                _levelBoss->zombies.at(j)->animator.animate(*_levelBoss->zombies.at(j)->getSprite());
                this->window->draw(*_levelBoss->zombies.at(j)->getSprite());
            }
            _levelBoss->getBoss()->animator.update(frame_time);
            _levelBoss->getBoss()->animator.animate(*_levelBoss->getBoss()->getSprite());
            if(!_levelBoss->getBoss()->isTube()) {
                this->window->draw(*_levelBoss->getBoss()->getSprite());
            }

            //Draw IU
            //If the game is paused, draw the menu
            if(_levelBoss->isLevelPause()) {
                this->window->draw(_levelBoss->getPauseMenu()->getTextStart());
                this->window->draw(_levelBoss->getPauseMenu()->getTextExit());
                this->window->draw(*_levelBoss->getPauseMenu()->getOptionIcon()->getSprite());
            }
            this->window->draw(_levelBoss->getTextTime());
            this->window->draw(*_levelBoss->getLivesFace()->getSprite());
            this->window->draw(_levelBoss->getTextLives());
            this->window->draw(*_levelBoss->getZombiesFace()->getSprite());
            this->window->draw(_levelBoss->getTextZombies());
            this->window->draw(_levelBoss->getTextFPS());
            this->window->draw(*_levelBoss->getJoystickImage()->getSprite());
            this->window->draw(*_levelBoss->getBorderBossLife());
            this->window->draw(*_levelBoss->getBossLife());
            this->window->draw(*_levelBoss->getTubeBoss()->getSprite());

            //EndGame
            if(_levelBoss->getPlayer()->getLives() <= 0) {
                this->window->draw(_levelBoss->getTextGameOver());
            }
        } else {
            if((_levelBoss->getClockSeconds() >= 5.7f && _levelBoss->getClockSeconds() < 6.f) && _levelBoss->getBoss()->isTube()) {
                _levelBoss->changeTubeSprite();
            }
        }
        //EndLevel
        //The screen will not move if there is not more blocks
        if(_levelBoss->getPlayer()->getSprite()->getPosition().x >= (_levelBoss->blocks.size() * _levelBoss->blocks.at(0)->getSprite()->getTexture()->getSize().x) - (this->window->getSize().x/2)) {
            _levelBoss->getPlayer()->setEndLevel(true);
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
