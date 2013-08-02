#include <iostream>
#include "../include/Level.h"


Level::Level(char file_music[]) {
    this->endGame = false;
    if (!this->font.loadFromFile("res/fonts/BrushRunes.otf")) {
        //error
    } else {
        this->timeText.setFont(this->font);
        this->timeText.setColor(sf::Color::Red);
        this->timeText.setPosition(512.f,55.f);
        this->livesText.setFont(this->font);
        this->livesText.setColor(sf::Color::Red);
        this->livesText.setPosition(70.f,55.f);
        this->zombiesText.setFont(this->font);
        this->zombiesText.setColor(sf::Color::Red);
        this->zombiesText.setPosition(970.f,55.f);
        this->gameOverText.setFont(this->font);
        this->gameOverText.setColor(sf::Color::Red);
        this->gameOverText.setPosition(362.f,384.f);
        this->gameOverText.setCharacterSize(150U);
        this->gameOverText.setString("Game Over");
        this->FPSText.setFont(this->font);
        this->FPSText.setColor(sf::Color::Red);
        this->FPSText.setPosition(730.f,55.f);
    }
    this->contZombies = 0;
    //I create the player and music in the level
    this->player1 = new Player((char*)"res/images/characters/players/player1.png");
    this->player1->getSprite()->setPosition(100.f,100.f);
    this->livesFace = new Object((char*)"res/images/characters/players/player1.png");
    this->zombiesFace = new Object((char*)"res/images/characters/npc/enemys/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
    sf::IntRect face;
    face.height = 26;
    face.left = 810;
    face.top = 272;
    face.width = 24;
    this->livesFace->setObjectVector(face);
    this->livesFace->getSprite()->setPosition(33.f,55.f);
    face.height = 23;
    face.left = 219;
    face.top = 383;
    face.width = 25;
    this->zombiesFace->setObjectVector(face);
    this->zombiesFace->getSprite()->setPosition(935.f,55.f);
    this->joystickImage = new Object((char*)"res/images/IU/no_joystick.png");
    this->joystickImage->getSprite()->setPosition(235.f,40.f);

    for(unsigned int i = 0; i< (sizeof(this->builders)/sizeof(this->builders[i])); i++) {
        this->builders[i] = new Builder((char*)"res/images/backgrounds/level1/builders.png");
        this->builders[i]->getSprite()->setPosition(i * this->builders[i]->getSprite()->getTexture()->getSize().x,804 - this->builders[i]->getSprite()->getTexture()->getSize().x );
    }

    for(unsigned int i = 0; i< (sizeof(this->skies)/sizeof(this->skies[i])); i++) {
        this->skies[i] = new Sky((char*)"res/images/backgrounds/level1/sky.png");
        this->skies[i]->getSprite()->setPosition(i * this->skies[i]->getSprite()->getTexture()->getSize().x,630 - this->skies[i]->getSprite()->getTexture()->getSize().x);
    }

    for(unsigned int i = 0; i < (sizeof(this->blocks)/sizeof(this->blocks[i])); i++) {
        this->blocks[i] = new Block((char*)"res/images/backgrounds/level1/block1.png");
        if(i > 320) {
            this->blocks[i]->getSprite()->setPosition((360-i) * this->blocks[i]->getSprite()->getTexture()->getSize().x,600);
        } else {
            this->blocks[i]->getSprite()->setPosition(i * this->blocks[i]->getSprite()->getTexture()->getSize().x,720);
        }
    }
    for(unsigned int i = 0; i < (sizeof(this->soldiers)/sizeof(this->soldiers[i])); i++) {
        this->soldiers[i] = new Object((char*)"res/images/characters/players/player1.png");
        sf::IntRect rect_aux = this->soldiers[i]->getObjectVector();
        if(i==0) {
            rect_aux.top = 296;
            rect_aux.left = 951;
            rect_aux.height = 134;
            rect_aux.width = 162;
            this->soldiers[i]->getSprite()->setPosition(160,585);
        } else if(i==1) {
            rect_aux.top = 713;
            rect_aux.left = 40;
            rect_aux.height = 55;
            rect_aux.width = 58;
            this->soldiers[i]->getSprite()->setPosition(100,665);
        } else if(i==2) {
            rect_aux.top = 142;
            rect_aux.left = 990;
            rect_aux.height = 54;
            rect_aux.width = 62;
            this->soldiers[i]->getSprite()->setPosition(200,665);
        } else {
            rect_aux.top = 226;
            rect_aux.left = 934;
            rect_aux.height = 36;
            rect_aux.width = 58;
            this->soldiers[i]->getSprite()->setPosition(600 * i,700.f);
        }
        this->soldiers[i]->setObjectVector(rect_aux);
        this->soldiers[i]->getSprite()->setScale(-1.f,1.f);

    }

    for(unsigned int i = 0; i < (sizeof(this->zombies)/sizeof(this->zombies[i])); i++) {
        this->zombies[i] = new Zombie((char*)"res/images/characters/npc/enemys/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
        this->zombies[i]->getSprite()->setPosition(((i+1)*300),100.f);
    }

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/level/gameover.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
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
}

Player* Level::getPlayer() {
    return this->player1;
}

void Level::moveUI(sf::RenderWindow *_window) {
    if(this->getPlayer()->getPosWindowX(_window) >= 512 && this->getPlayer()->getSprite()->getPosition().x <= 9728) {
        this->timeText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 8.f,55.f);
        this->livesText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 450.f,55.f);
        this->livesFace->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 487.f,55.f);
        this->zombiesText.setPosition(this->getPlayer()->getSprite()->getPosition().x + 450.f,55.f);
        this->zombiesFace->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x + 415.f,55.f);
        this->gameOverText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 158.f ,384.f);
        this->FPSText.setPosition(this->getPlayer()->getSprite()->getPosition().x + 210.f,55.f);
        this->joystickImage->getSprite()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 278.f, 40.f);
    }
}
sf::Text Level::getTextTime() {
    this->time = this->clockTime.getElapsedTime();
    //Convert time to string
    std::stringstream timeString;
    timeString << "Time: " <<(int)this->time.asSeconds();
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

int Level::getContZombies() {
    return this->contZombies;
}

void Level::setContZombies(int _contZombies) {
    this->contZombies = _contZombies;
}

void Level::restart() {
    this->music->stop();
    //IU
    this->timeText.setPosition(512.f,55.f);
    this->livesText.setPosition(70.f,55.f);
    this->zombiesText.setPosition(970.f,55.f);
    this->livesFace->getSprite()->setPosition(33.f,55.f);
    this->zombiesFace->getSprite()->setPosition(935.f,55.f);
    this->gameOverText.setPosition(362.f,384.f);

    //Enemys
    for(unsigned int i = 0; i < (sizeof(this->zombies)/sizeof(this->zombies[i])); i++) {
        this->zombies[i]->getSprite()->setOrigin(27.5f,32.f);
        this->zombies[i]->getSprite()->setScale(-1.f,1.f);
        this->zombies[i]->setmovingRight(false);
        this->zombies[i]->setmovingLeft(true);
        this->zombies[i]->setEndJumping(false);
        this->zombies[i]->setLife(true);
        this->zombies[i]->getSprite()->setPosition(((i+1)*300),100.f);
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
