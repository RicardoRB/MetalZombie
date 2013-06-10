#include "../include/Level.h"
#include <iostream>
#include <sstream>

Level::Level(char file_music[],char file_image_background[])
{
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
    }
    this->contZombies = 0;
    //I create the player and music in the level
    this->player1 = new Player((char*)"res/images/characters/players/player1.png");
    this->livesFace = new Object((char*)"res/images/characters/players/player1.png");
    this->zombiesFace = new Object((char*)"res/images/characters/npc/enemys/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
    sf::IntRect cara;
    cara.height = 26;
    cara.left = 810;
    cara.top = 272;
    cara.width = 24;
    this->livesFace->setObjectVector(cara);
    this->livesFace->getSpriteObject()->setPosition(33.f,55.f);
    cara.height = 23;
    cara.left = 219;
    cara.top = 383;
    cara.width = 25;
    this->zombiesFace->setObjectVector(cara);
    this->zombiesFace->getSpriteObject()->setPosition(935.f,55.f);
    this->music = new sf::Music();
    if(!music->openFromFile(file_music)) {
//        std::cout << "Error music in level" << std::endl;
    } else {
        this->music->openFromFile(file_music);
    }
    this->music->play();
    this->music->setLoop(true);
    this->backgroundImage.loadFromFile(file_image_background);

    for(unsigned int i = 0; i < (sizeof(this->zombies)/sizeof(this->zombies[i])); i++) {
        this->zombies[i] = new Zombie((char*)"res/images/characters/npc/enemys/zombies/cool_zombie_sprite_by_gvbn10-d39mzxg.png");
        this->zombies[i]->getSprite()->setPosition(((i+1)*300),100.f);
    }

    for(unsigned int i = 0; i< (sizeof(this->builders)/sizeof(this->builders[i])); i++) {
        this->builders[i] = new Builder((char*)"res/images/backgrounds/level1/builders.png");
        this->builders[i]->getSpriteObject()->setPosition(i * this->builders[i]->getSpriteObject()->getTexture()->getSize().x,804 - this->builders[i]->getSpriteObject()->getTexture()->getSize().x );
    }

    for(unsigned int i = 0; i< (sizeof(this->skies)/sizeof(this->skies[i])); i++) {
        this->skies[i] = new Sky((char*)"res/images/backgrounds/level1/sky.png");
        this->skies[i]->getSpriteObject()->setPosition(i * this->skies[i]->getSpriteObject()->getTexture()->getSize().x,630 - this->skies[i]->getSpriteObject()->getTexture()->getSize().x);
    }

    for(unsigned int i = 0; i < (sizeof(this->blocks)/sizeof(this->blocks[i])); i++) {
        this->blocks[i] = new Block((char*)"res/images/backgrounds/level1/block1.png");
        this->blocks[i]->getSpriteObject()->setPosition(i * this->blocks[i]->getSpriteObject()->getTexture()->getSize().x,720);
    }
    for(unsigned int i = 0; i< (sizeof(this->soldiers)/sizeof(this->soldiers[i])); i++) {
        this->soldiers[i] = new Object((char*)"res/images/characters/players/player1.png");
        sf::IntRect rect_aux = this->soldiers[i]->getObjectVector();
        switch(i) {
        case 0:
            rect_aux.top = 296;
            rect_aux.left = 951;
            rect_aux.height = 134;
            rect_aux.width = 162;
            this->soldiers[i]->getSpriteObject()->setPosition(160,585);
            break;
        case 1:
            rect_aux.top = 713;
            rect_aux.left = 40;
            rect_aux.height = 55;
            rect_aux.width = 58;
            this->soldiers[i]->getSpriteObject()->setPosition(100,665);
            break;
        case 2:
            rect_aux.top = 142;
            rect_aux.left = 990;
            rect_aux.height = 54;
            rect_aux.width = 62;
            this->soldiers[i]->getSpriteObject()->setPosition(200,665);
            break;
        case 3:

            break;
        default:
            break;
            //instrucción(es);
        };
        this->soldiers[i]->setObjectVector(rect_aux);
        this->soldiers[i]->getSpriteObject()->setScale(-1.f,1.f);

    }
}

Level::~Level()
{
    delete zombies;
    delete player1;
    delete music;
    delete blocks;
    delete builders;
    delete livesFace;
}

Player* Level::getPlayer()
{
    return this->player1;
}

void Level::moveIU()
{
    if(this->getPlayer()->getPosWindowX() >= 512 && this->getPlayer()->getSprite()->getPosition().x <= 9728) {
        this->timeText.setPosition(this->getPlayer()->getSprite()->getPosition().x,55.f);
        this->livesText.setPosition(this->getPlayer()->getSprite()->getPosition().x - 442.f,55.f);
        this->livesFace->getSpriteObject()->setPosition(this->getPlayer()->getSprite()->getPosition().x - 479.f,55.f);
        this->zombiesText.setPosition(this->getPlayer()->getSprite()->getPosition().x + 479.f,55.f);
        this->zombiesFace->getSpriteObject()->setPosition(this->getPlayer()->getSprite()->getPosition().x + 442.f,55.f);
    }
}
sf::Text Level::getTextTime()
{
    this->time = this->clockTime.getElapsedTime();
    //Convert time to string
    std::stringstream timeString;
    timeString << "Time: " <<(int)this->time.asSeconds();
    this->timeText.setString(timeString.str());
    return this->timeText;
}

sf::Clock Level::getClockTime()
{
    return this->clockTime;
}

sf::Time Level::getTime()
{
    return this->time;
}

Object* Level::getLivesFace()
{
    return this->livesFace;
}

sf::Text Level::getTextLives()
{
    std::stringstream livesString;
    livesString << "x " << this->getPlayer()->getLives();
    this->livesText.setString(livesString.str());
    return this->livesText;
}

Object* Level::getZombiesFace()
{
    return this->zombiesFace;
}

sf::Text Level::getTextZombies()
{
    std::stringstream zombiesString;
    zombiesString << "x " << this->getContZombies();
    this->zombiesText.setString(zombiesString.str());
    return this->zombiesText;
}

int Level::getContZombies()
{
    return this->contZombies;
}

void Level::setContZombies(int _contZombies)
{
    this->contZombies = _contZombies;
}
