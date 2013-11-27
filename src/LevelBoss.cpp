#include "../include/LevelBoss.h"
#include <iostream>

LevelBoss::LevelBoss() {
    //ctor
}

LevelBoss::LevelBoss(char background_texture[],char file_music[],float windowWidth, float windowHeight,const unsigned int numZombies,const unsigned int numBlocks) {
    this->clockTime.start();
    this->endGame = false;
    this->pauseMenu = new Menu();
    this->backgroundBoss = new Object(background_texture);
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

    this->bossLife = new sf::RectangleShape(sf::Vector2f(windowWidth/2, 10.f));
    this->bossLife->setPosition(windowWidth/4,150.f);
    this->bossLife->setFillColor(sf::Color(88, 208, 128));
    this->borderBossLife = new sf::RectangleShape(sf::Vector2f(windowWidth/2, 10.f));
    this->borderBossLife->setPosition(windowWidth/4,150.f);
    this->borderBossLife->setFillColor(sf::Color(35,35,35));
    this->borderBossLife->setOutlineColor(sf::Color::Black);
    this->borderBossLife->setOutlineThickness(5.f);


    for(unsigned int i = 0; i < numBlocks; i++) {
        if(i==0) {
            this->blocks.push_back(new Object((char*)"res/images/backgrounds/level1/block1.png"));
        } else {
            this->blocks.push_back(new Object((this->blocks.at(0)->getTexture())));
        }
        this->blocks.at(i)->getSprite()->setPosition(i * this->blocks.at(i)->getSprite()->getTexture()->getSize().x,windowHeight - this->blocks.at(i)->getSprite()->getTexture()->getSize().y);
    }
    int blockPosition1 = 0;
    int blockPosition2 = this->blocks.size() - 1;

    for(unsigned int i = 0; i < 8; i++) {
        this->platforms.push_back(new Object((this->blocks.at(0)->getTexture())));
        if(i % 2 == 0) {
            this->platforms.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition1)->getSprite()->getPosition().x,this->blocks.at(blockPosition2)->getSprite()->getPosition().y - 140.f);
            blockPosition1++;
        } else {
            this->platforms.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition2)->getSprite()->getPosition().x,this->blocks.at(blockPosition2)->getSprite()->getPosition().y - 140.f);
            blockPosition2--;
        }
    }

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/level/gameover.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
    }

    this->player1 = new Player((char*)"res/images/characters/players/player1.png", windowWidth);
    this->player1->getSprite()->setPosition(1.f,100.f);

    blockPosition1 = 0;
    blockPosition2 = this->blocks.size() - 1;

    for(unsigned int i = 0; i < numZombies; i++) {
        if(i==0) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png",60.f,400.f,0));
        } else if(i < 6) {
            this->zombies.push_back(new Zombie(this->zombies.at(0)->getTexture(),60.f,400.f,0));
        } else if(i == 6) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/fastZombie.png",200.f,400.f,0));
        } else if(i < 12) {
            this->zombies.push_back(new Zombie(this->zombies.at(6)->getTexture(),200.f,400.f,0));
        } else if(i == 12) {
            this->zombies.push_back(new Zombie((char*)"res/images/characters/npc/enemy/zombies/bigZombie.png",40.f,400.f,2));
        } else {
            this->zombies.push_back(new Zombie(this->zombies.at(12)->getTexture(),40.f,400.f,2));
        }
        if(i % 2 == 0) {
            this->zombies.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition1)->getSprite()->getPosition().x + 35.f,200.f);
            blockPosition1++;
        } else {
            this->zombies.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition2)->getSprite()->getPosition().x,200.f);
            blockPosition2--;
        }
    }
    this->boss = new ZombieBoss((char*)"res/images/characters/npc/enemy/zombies/Resident_Evil_Tyrant_Sprites_by_DC_TommyP.png",250.f,400.f,5,3);
    this->boss->getSprite()->setPosition(100,500);
    this->tubeBoss = new Object(this->boss->getTexture());
    face.height = 185;
    face.left = 46;
    face.top = 679;
    face.width = 113;
    this->tubeBoss->setObjectVector(face);
    this->tubeBoss->getSprite()->setPosition(100.f,100.f);
    this->timeTube = new thor::StopWatch();

    this->music = new sf::Music();
    if(!music->openFromFile(file_music)) {
//        std::cout << "Error music in level" << std::endl;
    } else {
        this->music->play();
        this->music->setLoop(true);
    }
    this->firstBlackScreen = false;
    this->zombiePhase = false;
    this->deadZombiesPhase = 0;
}

LevelBoss::~LevelBoss() {
    //dtor
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
    delete backgroundBoss;
    delete boss;
    delete bossLife;
    delete borderBossLife;
    delete tubeBoss;
    delete timeTube;
}

Object* LevelBoss::getBackgroundBoss() {
    return this->backgroundBoss;
}

sf::RectangleShape* LevelBoss::getBossLife() {
    return this->bossLife;
}

sf::RectangleShape* LevelBoss::getBorderBossLife() {
    return this->borderBossLife;
}

Object* LevelBoss::getTubeBoss() {
    return this->tubeBoss;
}

ZombieBoss* LevelBoss::getBoss() {
    return this->boss;
}

void LevelBoss::changeTubeSprite() {
    sf::IntRect tube;
    tube.height = 185;
    tube.top = 679;
    tube.width = 113;
    if(this->boss->isTube()) {
        this->boss->setTube(false);
        tube.left = 291;
    } else {
        this->boss->setTube(true);
        this->boss->setLives(this->boss->getMaxLives());
        tube.left = 46;
    }
    this->tubeBoss->setObjectVector(tube);

}

void LevelBoss::reduceLifeBar() {
    this->bossLife->setSize(sf::Vector2f((this->boss->getLives()*this->borderBossLife->getSize().x) / this->boss->getMaxLives(),this->bossLife->getSize().y));
}

void LevelBoss::restart(float windowWidth, float windowHeight) {
    this->music->stop();
    int blockPosition1 = 0;
    int blockPosition2 = this->blocks.size() - 1;
    //Enemys
    for(unsigned int i = 0; i < zombies.size(); i++) {
        this->zombies.at(i)->getSprite()->setOrigin(27.5f,32.f);
        this->zombies.at(i)->getSprite()->setScale(-1.f,1.f);
        this->zombies.at(i)->setVelX(0);
        this->zombies.at(i)->setmovingRight(false);
        this->zombies.at(i)->setmovingLeft(false);
        this->zombies.at(i)->setEndJumping(false);
        this->zombies.at(i)->setLife(true);
        if(i % 2 == 0) {
            this->zombies.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition1)->getSprite()->getPosition().x + 35.f,200.f);
            blockPosition1++;
        } else {
            this->zombies.at(i)->getSprite()->setPosition(this->blocks.at(blockPosition2)->getSprite()->getPosition().x,200.f);
            blockPosition2--;
        }
    }
    //Boss
    this->boss->setLife(true);
    this->boss->setLives(this->boss->getMaxLives());
    this->boss->setRecoverys(this->boss->getMaxRecoverys());
    this->bossLife->setSize(sf::Vector2f((this->boss->getLives()*this->borderBossLife->getSize().x) / this->boss->getMaxLives(),this->bossLife->getSize().y));
    this->boss->setmovingRight(false);
    this->boss->setmovingLeft(true);
    this->boss->setEndJumping(false);
    this->boss->setFalling(true);
    if(!this->boss->isTube()) {
        this->changeTubeSprite();
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
    this->firstBlackScreen = false;
    this->zombiePhase = false;
    this->deadZombiesPhase = 0;
    this->clockTime.reset();
    this->clockTime.start();
    this->timeTube->reset();
}

thor::StopWatch* LevelBoss::getTimeTube() {
    return this->timeTube;
}

bool LevelBoss::isFirstBlackScreen() {
    return this->firstBlackScreen;
}

void LevelBoss::setFirstBlackScreen(bool _firstBlackScreen) {
    this->firstBlackScreen = _firstBlackScreen;
}

bool LevelBoss::isZombiePhase() {
    return this->zombiePhase;
}

void LevelBoss::setZombiePhase(bool _zombiePhase) {
    this->zombiePhase = _zombiePhase;
}

int LevelBoss::getDeadZombiesPhase() {
    return this->deadZombiesPhase;
}
void LevelBoss::setDeadZombiesPhase(int _deadZombiesPhase) {
    this->deadZombiesPhase = _deadZombiesPhase;
}
