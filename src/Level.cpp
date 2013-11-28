#include "../include/Level.h"

Level::Level() {

}

Level::Level(char file_music[],float windowWidth, float windowHeight,const unsigned int numZombies,const unsigned int numBlocks,const unsigned int numBuilders,const unsigned int numSkies,const unsigned int numSoldiers) {
    this->clockTime.start();
    this->endGame = false;
    this->pauseMenu = new Menu();
    if (!this->font.loadFromFile("res/fonts/BrushRunes.otf")) {
        //error
    } else {
        this->timeText.setFont(this->font);
        this->timeText.setColor(sf::Color::Red);
        this->timeText.setPosition(windowWidth/2,(windowHeight + 55.f) - windowHeight);
        this->livesText.setFont(this->font);
        this->livesText.setColor(sf::Color::Red);
        this->livesText.setPosition((windowWidth/2)-442.f,(windowHeight + 55.f) - windowHeight);
        this->zombiesText.setFont(this->font);
        this->zombiesText.setColor(sf::Color::Red);
        this->zombiesText.setPosition((windowWidth/2)+458.f,(windowHeight + 55.f) - windowHeight);
        this->gameOverText.setFont(this->font);
        this->gameOverText.setColor(sf::Color::Red);
        this->gameOverText.setPosition((windowWidth/2)-150.f,(windowHeight/2)-128.f);
        this->gameOverText.setCharacterSize(150U);
        this->gameOverText.setString("Game Over");
        this->FPSText.setFont(this->font);
        this->FPSText.setColor(sf::Color::Red);
        this->FPSText.setPosition((windowWidth/2)+218.f,(windowHeight + 55.f) - windowHeight);
        this->pauseMenu->setOption(0);
        this->pauseMenu->getOptionIcon()->getSprite()->setPosition((windowWidth/2)-110.f,(windowHeight/2)+10.f);
        this->pauseMenu->setTextStart(sf::Text("Resume",this->font, 80U),sf::Color::Red,sf::Vector2f((windowWidth/2)-60.5f,(windowHeight/2)-20.f));
        this->pauseMenu->setTextExit(sf::Text("Exit",this->font, 80U),sf::Color::Red,sf::Vector2f((windowWidth/2)-35.5f,(windowHeight/2)+65.f));
    }
    this->contZombies = 0;

    this->livesFace = new Object((char*)"res/images/characters/players/player1.png");
    this->zombiesFace = new Object((char*)"res/images/characters/npc/enemy/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
    sf::IntRect face;
    face.height = 26;
    face.left = 810;
    face.top = 272;
    face.width = 24;
    this->livesFace->setObjectVector(face);
    this->livesFace->getSprite()->setPosition((windowWidth/2)-479.f,(windowHeight + 55.f) - windowHeight);
    face.height = 23;
    face.left = 219;
    face.top = 383;
    face.width = 25;
    this->zombiesFace->setObjectVector(face);
    this->zombiesFace->getSprite()->setPosition((windowWidth/2)+423.f,(windowHeight + 55.f) - windowHeight);
    this->joystickImage = new Object((char*)"res/images/IU/no_joystick.png");
    this->joystickImage->getSprite()->setPosition((windowWidth/2)-277.f,(windowHeight + 55.f) - windowHeight);
    int j=0;
    for(unsigned int i = 0; i < numBlocks; i++) {
        if(i==0) {
            this->blocks.push_back(new Object((char*)"res/images/backgrounds/level1/block1.png"));
        } else {
            this->blocks.push_back(new Object((this->blocks.at(0)->getTexture())));
        }
        if(i >= 100 && i <= 110) {
            this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - 180);
        } else if (i >= 111 && i <= 115) {
            this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - 300);
        } else if(i >= 200 && i <= 220) {
            this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks.at(i)->getSprite()->getTexture()->getSize().y);
        } else if (i >= 230 && i <= 260) {
            j += 4;
            this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - 180+j);
        } else {
            this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks.at(i)->getSprite()->getTexture()->getSize().y);
        }
    }

    for(unsigned int i = 0; i< numBuilders; i++) {
        if(i==0) {
            this->builders.push_back(new Object((char*)"res/images/backgrounds/level1/builders.png"));
        } else {
            this->builders.push_back(new Object(this->builders.at(0)->getTexture()));
        }
        this->builders.at(i)->getSprite()->setPosition(i * this->builders.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - this->builders.at(i)->getSprite()->getTexture()->getSize().y - this->blocks.at(i)->getSprite()->getTexture()->getSize().y);
    }

    for(unsigned int i = 0; i< numSkies; i++) {
        if(i==0) {
            this->skies.push_back(new Object((char*)"res/images/backgrounds/level1/sky.png"));
        } else {
            this->skies.push_back(new Object(this->skies.at(0)->getTexture()));
        }
        this->skies.at(i)->getSprite()->setPosition(i * this->skies.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks.at(i)->getSprite()->getTexture()->getSize().y - 246.f - this->skies.at(i)->getSprite()->getTexture()->getSize().y);
    }

    for(unsigned int i = 0; i < numSoldiers; i++) {
        if(i==0) {
            this->soldiers.push_back(new Object((char*)"res/images/characters/players/player1.png"));
        } else {
            this->soldiers.push_back(new Object(this->soldiers.at(0)->getTexture()));
        }

        sf::IntRect rect_aux = this->soldiers.at(i)->getObjectVector();
        if(i==0) {
            rect_aux.top = 296;
            rect_aux.left = 951;
            rect_aux.height = 134;
            rect_aux.width = 162;
            this->soldiers.at(i)->getSprite()->setPosition(160,windowHeight - (this->blocks.at(0)->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else if(i==1) {
            rect_aux.top = 713;
            rect_aux.left = 40;
            rect_aux.height = 55;
            rect_aux.width = 58;
            this->soldiers.at(i)->getSprite()->setPosition(100,windowHeight - (this->blocks.at(0)->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else if(i==2) {
            rect_aux.top = 142;
            rect_aux.left = 990;
            rect_aux.height = 54;
            rect_aux.width = 62;
            this->soldiers.at(i)->getSprite()->setPosition(200,windowHeight - (this->blocks.at(0)->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else {
            rect_aux.top = 226;
            rect_aux.left = 934;
            rect_aux.height = 36;
            rect_aux.width = 58;
            //I put -15.f because if I don't put it, the soldier will be float, because the arm is more longer than the body
            this->soldiers.at(i)->getSprite()->setPosition(600 * i,windowHeight - (this->blocks.at(0)->getSprite()->getTexture()->getSize().y + rect_aux.height - 15.f));
        }
        this->soldiers.at(i)->setObjectVector(rect_aux);
        this->soldiers.at(i)->getSprite()->setScale(-1.f,1.f);

    }

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/level/gameover.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
    }


    this->player1 = new Player((char*)"res/images/characters/players/player1.png", windowWidth);
    this->player1->getSprite()->setPosition(1.f,100.f);

    for(unsigned int i = 0; i < numZombies; i++) {
        if(i==0) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png",60.f,400.f,0));
        } else if(i < 10) {
            this->zombies.push_back(new Zombie(this->zombies.at(0)->getTexture(),60.f,400.f,0));
        } else if(i == 10) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/fastZombie.png",200.f,400.f,0));
        } else if(i < 20) {
            this->zombies.push_back(new Zombie(this->zombies.at(10)->getTexture(),200.f,400.f,0));
        } else if(i == 20) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/bigZombie.png",40.f,400.f,2));
        } else {
            this->zombies.push_back(new Zombie(this->zombies.at(20)->getTexture(),40.f,400.f,2));
        }
        this->zombies.at(i)->getSprite()->setPosition(((i+1.f)*200.f),100.f);
    }

    this->music = new sf::Music();
    if(!music->openFromFile(file_music)) {
//        std::cout << "Error music in level" << std::endl;
    } else {
        this->music->play();
        this->music->setLoop(true);
    }
}

Level::~Level() {
    for(unsigned int i = 0; i < zombies.size(); i++) {
        delete zombies.at(i);
    }
    for(unsigned int i = 0; i < blocks.size(); i++) {
        delete blocks.at(i);
    }
    for(unsigned int i = 0; i < platforms.size(); i++) {
        delete platforms.at(i);
    }
    for(unsigned int i = 0; i < builders.size(); i++) {
        delete builders.at(i);
    }
    for(unsigned int i = 0; i < skies.size(); i++) {
        delete skies.at(i);
    }
    for(unsigned int i = 0; i < soldiers.size(); i++) {
        delete soldiers.at(i);
    }
    delete player1;
    delete music;
    delete livesFace;
    delete zombiesFace;
    delete joystickImage;
    delete bufferEffect;
    delete soundEffect;
    delete pauseMenu;
}

Player* Level::getPlayer() {
    return this->player1;
}

void Level::moveUI(sf::RenderWindow *_window) {
    if(this->getPlayer()->getPosWindowX(_window) >= (_window->getSize().x/2) && this->getPlayer()->getSprite()->getPosition().x <= (blocks.size() * blocks.at(0)->getSprite()->getTexture()->getSize().x) - (_window->getSize().x/2)) {
        this->timeText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 8.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->livesText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 450.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->livesFace->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 487.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->zombiesText.setPosition(this->getPlayer()->getSprite()->getPosition().x + 450.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->zombiesFace->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x + 415.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->gameOverText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 158.f ,384.f);
        this->FPSText.setPosition(this->getPlayer()->getSprite()->getPosition().x + 210.f,(_window->getSize().y + 55.f) - _window->getSize().y);
        this->joystickImage->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 278.f, (_window->getSize().y + 55.f) - _window->getSize().y);
        this->pauseMenu->getOptionIcon()->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 110.f, this->pauseMenu->getOptionIcon()->getSprite()->getPosition().y);
        this->pauseMenu->setTextStart(sf::Text("Resume",this->font, 80U),sf::Color::Red,sf::Vector2f(this->getPlayer()->getSprite()->getPosition().x - 60.5f,this->pauseMenu->getTextStart().getPosition().y));
        this->pauseMenu->setTextExit(sf::Text("Exit",this->font, 80U),sf::Color::Red,sf::Vector2f(this->getPlayer()->getSprite()->getPosition().x - 35.5f,this->pauseMenu->getTextExit().getPosition().y));
    }
}
sf::Text Level::getTextTime() {
    //Convert time to string
    std::stringstream timeString;
    timeString << "Time: " <<(int)this->clockTime.getElapsedTime().asSeconds();
    this->timeText.setString(timeString.str());
    return this->timeText;
}

Object* Level::getLivesFace() {
    return this->livesFace;
}

sf::Text Level::getTextLives() {
    std::stringstream livesString;
    livesString << "x " << this->getPlayer()->getLives();
    this->livesText.setString(livesString.str());
    return this->livesText;
}

sf::Text Level::getTextGameOver() {
    if(!this->endGame) {
        this->soundEffect->play();
        this->endGame = true;
    }
    return this->gameOverText;
}


Object* Level::getZombiesFace() {
    return this->zombiesFace;
}

Object* Level::getJoystickImage() {
    return this->joystickImage;
}

sf::Text Level::getTextZombies() {
    std::stringstream zombiesString;
    zombiesString << "x " << this->getContZombies();
    this->zombiesText.setString(zombiesString.str());
    return this->zombiesText;
}

sf::Text Level::getTextFPS() {
    std::stringstream FPSString;
    FPSString << "FPS: " << (int)this->fps;
    this->FPSText.setString(FPSString.str());
    return this->FPSText;
}

sf::Text Level::getTextResume() {
    return this->pauseMenu->getTextStart();
}

sf::Text Level::getTextExit() {
    return this->pauseMenu->getTextExit();
}

int Level::getContZombies() {
    return this->contZombies;
}

void Level::setContZombies(int _contZombies) {
    this->contZombies = _contZombies;
}

void Level::restart(float windowWidth, float windowHeight) {
    this->music->stop();
    //IU
    this->timeText.setPosition(windowWidth/2,(windowHeight + 55.f) - windowHeight);
    this->livesText.setPosition((windowWidth/2)-442.f,(windowHeight + 55.f) - windowHeight);
    this->zombiesText.setPosition((windowWidth/2)+458.f,(windowHeight + 55.f) - windowHeight);
    this->gameOverText.setPosition((windowWidth/2)-150.f,(windowHeight/2)-128.f);
    this->FPSText.setPosition((windowWidth/2)+218.f,(windowHeight + 55.f) - windowHeight);
    this->livesFace->getSprite()->setPosition((windowWidth/2)-479.f,(windowHeight + 55.f) - windowHeight);
    this->zombiesFace->getSprite()->setPosition((windowWidth/2)+423.f,(windowHeight + 55.f) - windowHeight);
    this->joystickImage->getSprite()->setPosition((windowWidth/2)-277.f,(windowHeight + 55.f) - windowHeight);
    this->pauseMenu->getOptionIcon()->getSprite()->setPosition((windowWidth/2)-110.f,(windowHeight/2)+10.f);
    this->pauseMenu->setTextStart(sf::Text("Resume",this->font, 80U),sf::Color::Red,sf::Vector2f((windowWidth/2)-60.5f,(windowHeight/2)-20.f));
    this->pauseMenu->setTextExit(sf::Text("Exit",this->font, 80U),sf::Color::Red,sf::Vector2f((windowWidth/2)-35.5f,(windowHeight/2)+65.f));

    //Enemys
    for(unsigned int i = 0; i < zombies.size(); i++) {
        this->zombies.at(i)->getSprite()->setOrigin(27.5f,32.f);
        this->zombies.at(i)->getSprite()->setScale(-1.f,1.f);
        this->zombies.at(i)->setmovingRight(false);
        this->zombies.at(i)->setmovingLeft(false);
        this->zombies.at(i)->setEndJumping(false);
        this->zombies.at(i)->setLife(true);
        this->zombies.at(i)->getSprite()->setPosition(((i+1)*200),100.f);
    }
    //Player
    this->getPlayer()->getSprite()->setOrigin(27.f,26.f);
    this->getPlayer()->getSprite()->setScale(-1.f,1.f);
    this->getPlayer()->setAttacking(false);
    this->getPlayer()->setmovingRight(false);
    this->getPlayer()->setmovingLeft(false);
    this->getPlayer()->setEndJumping(false);
    this->getPlayer()->setLife(true);
    this->getPlayer()->getSprite()->setPosition(100.f,100.f);

    this->contZombies = 0;
    this->music->play();
    this->music->setLoop(true);
    this->clockTime.reset();
    this->clockTime.start();
}

void Level::verticalSpeed(Character *_character, float speedY) {
    if(_character->isEndJumping()) {
        _character->setVelY(this->gravity);
    } else if(_character->getVelY() < this->gravity) {
        _character->setVelY(_character->getVelY() + speedY);
    } else if(_character->getVelY() > this->gravity) {
        _character->setVelY(this->gravity);
    }
}

void Level::horizontalSpeed(Character *_character, float MaxSpeedX, float decreaseX) {
    if(_character->getVelX() > MaxSpeedX) {
        _character->setVelX(_character->getVelX() + decreaseX);
    } else if(_character->getVelX() < -MaxSpeedX) {
        _character->setVelX(_character->getVelX() + decreaseX);
    } else {
        _character->setVelX(0.f);
    }
}

float Level::getFPS() {
    return this->fps;
}

void Level::setFPS(float _fps) {
    this->fps = _fps;
}

void Level::blockCollision(Character *_character, std::vector<Object*> _blocks) {
    for(unsigned int i = 0; i < _blocks.size(); i++) {
        if(_blocks.at(i)->getSprite()->getGlobalBounds().intersects(_character->getSprite()->getGlobalBounds()) && _character->isFalling()) {
            _character->setEndJumping(true);
            _character->setJumping(false);
            _character->getSprite()->setPosition(_character->getSprite()->getPosition().x,
                                                 _blocks.at(i)->getSprite()->getPosition().y - (_character->getSprite()->getOrigin().y));
        }
    }
}

void Level::pauseLevel() {
    this->clockTime.stop();
}

void Level::resumeLevel() {
    this->clockTime.start();
}

bool Level::isLevelPause() {
    return !this->clockTime.isRunning();
}

Menu* Level::getPauseMenu() {
    return this->pauseMenu;
}

float Level::getClockSeconds() {
    return this->clockTime.getElapsedTime().asSeconds();
}

sf::Music* Level::getMusic(){
    return this->music;
}
