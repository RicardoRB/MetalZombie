#include "../include/Level.h"
#include <iostream>

Level::Level(char file_music[],char file_image_background[])
{
    //I create the player and music in the level
    this->player1 = new Player((char*)"res/images/characters/players/player1.png");
    this->music = new sf::Music();
    if(!music->openFromFile(file_music)) {
//        std::cout << "Error music in level" << std::endl;
    } else {
        this->music->openFromFile(file_music);
    }
    this->music->play();
    this->music->setLoop(true);
    this->backgroundImage.loadFromFile(file_image_background);

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
}

Level::~Level()
{
    delete player1;
    delete music;
    delete blocks;
    delete builders;
}

Player* Level::getPlayer()
{
    return this->player1;
}
