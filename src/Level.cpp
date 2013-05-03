#include "../include/Level.h"
#include <iostream>

Level::Level(char file_music[],char file_image[])
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
    this->backgroundImage.loadFromFile(file_image);
    this->background.setTexture(backgroundImage);
    for(int i = 0; i < 32; i++) {
        blocks[i] = new Block((char*)"res/images/blocks/block_level1.png");
        blocks[i]->getBlock()->setPosition(i * 32,720);
    }
}

Level::~Level()
{
    delete player1;
    delete music;
}
