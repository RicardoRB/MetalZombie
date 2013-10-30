#include <iostream>
#include "../include/Level.h"


Level::Level(char file_music[],float windowWidth, float windowHeight) {
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

    for(unsigned int i = 0; i < (sizeof(this->blocks)/sizeof(this->blocks[i])); i++) {
        this->blocks[i] = new Block((char*)"res/images/backgrounds/level1/block1.png");
        if(i > 320) {
            this->blocks[i]->getSprite()->setPosition((360-i) * this->blocks[i]->getSprite()->getTexture()->getSize().x,windowHeight - 180.f);
        } else {
            this->blocks[i]->getSprite()->setPosition(i * this->blocks[i]->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks[i]->getSprite()->getTexture()->getSize().y);
        }
    }

    for(unsigned int i = 0; i< (sizeof(this->builders)/sizeof(this->builders[i])); i++) {
        this->builders[i] = new Builder((char*)"res/images/backgrounds/level1/builders.png");
        this->builders[i]->getSprite()->setPosition(i * this->builders[i]->getSprite()->getTexture()->getSize().x,windowHeight - this->builders[i]->getSprite()->getTexture()->getSize().y - this->blocks[i]->getSprite()->getTexture()->getSize().y);
    }

    for(unsigned int i = 0; i< (sizeof(this->skies)/sizeof(this->skies[i])); i++) {
        this->skies[i] = new Sky((char*)"res/images/backgrounds/level1/sky.png");
        this->skies[i]->getSprite()->setPosition(i * this->skies[i]->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks[i]->getSprite()->getTexture()->getSize().y - 246.f - this->skies[i]->getSprite()->getTexture()->getSize().y);
    }

    for(unsigned int i = 0; i < (sizeof(this->soldiers)/sizeof(this->soldiers[i])); i++) {
        this->soldiers[i] = new Object((char*)"res/images/characters/players/player1.png");
        sf::IntRect rect_aux = this->soldiers[i]->getObjectVector();
        if(i==0) {
            rect_aux.top = 296;
            rect_aux.left = 951;
            rect_aux.height = 134;
            rect_aux.width = 162;
            this->soldiers[i]->getSprite()->setPosition(160,windowHeight - (this->blocks[0]->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else if(i==1) {
            rect_aux.top = 713;
            rect_aux.left = 40;
            rect_aux.height = 55;
            rect_aux.width = 58;
            this->soldiers[i]->getSprite()->setPosition(100,windowHeight - (this->blocks[0]->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else if(i==2) {
            rect_aux.top = 142;
            rect_aux.left = 990;
            rect_aux.height = 54;
            rect_aux.width = 62;
            this->soldiers[i]->getSprite()->setPosition(200,windowHeight - (this->blocks[0]->getSprite()->getTexture()->getSize().y + rect_aux.height));
        } else {
            rect_aux.top = 226;
            rect_aux.left = 934;
            rect_aux.height = 36;
            rect_aux.width = 58;
            //I put -15.f because if I don't put it, the soldier will be float, because the arm is more longer than the body
            this->soldiers[i]->getSprite()->setPosition(600 * i,windowHeight - (this->blocks[0]->getSprite()->getTexture()->getSize().y + rect_aux.height - 15.f));
        }
        this->soldiers[i]->setObjectVector(rect_aux);
        this->soldiers[i]->getSprite()->setScale(-1.f,1.f);

    }

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/level/gameover.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
    }

    this->player1 = new Player((char*)"res/images/characters/players/player1.png", windowWidth);
    this->player1->getSprite()->setPosition(100.f,100.f);

    for(unsigned int i = 0; i < (sizeof(this->zombies)/sizeof(this->zombies[i])); i++) {
        this->zombies[i] = new Zombie((char*)"res/images/characters/npc/enemy/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
        this->zombies[i]->getSprite()->setPosition(((i+1.f)*300.f),100.f);
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
    delete zombies;
    delete blocks;
    delete builders;
    delete skies;
    delete soldiers;
    delete player1;
    delete music;
    delete livesFace;
    delete zombiesFace;
    delete joystickImage;
    delete backgroundBoss;
    delete bufferEffect;
    delete soundEffect;
    delete pauseMenu;
}

Player* Level::getPlayer() {
    return this->player1;
}

void Level::moveUI(sf::RenderWindow *_window) {
    if(this->getPlayer()->getPosWindowX(_window) >= (_window->getSize().x/2) && this->getPlayer()->getSprite()->getPosition().x <= 9728) {
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
    for(unsigned int i = 0; i < (sizeof(this->zombies)/sizeof(this->zombies[i])); i++) {
        this->zombies[i]->getSprite()->setOrigin(27.5f,32.f);
        this->zombies[i]->getSprite()->setScale(-1.f,1.f);
        this->zombies[i]->setmovingRight(false);
        this->zombies[i]->setmovingLeft(true);
        this->zombies[i]->setEndJumping(false);
        this->zombies[i]->setLife(true);
        this->zombies[i]->getSprite()->setPosition(((i+1)*500),100.f);
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

void Level::blockCollision(Character *_character) {
    for(unsigned int i = 0; i < (sizeof(this->blocks)/sizeof(this->blocks[i])); i++) {
        if(this->blocks[i]->getSprite()->getGlobalBounds().intersects(_character->getSprite()->getGlobalBounds()) && _character->isFalling()) {
            _character->setEndJumping(true);
            _character->setJumping(false);
            _character->getSprite()->setPosition(_character->getSprite()->getPosition().x,
                                                 this->blocks[i]->getSprite()->getPosition().y - (_character->getSprite()->getOrigin().y));
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
