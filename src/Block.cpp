#include "../include/Block.h"

Block::Block()
{
    //ctor
}

Block::Block(char file_texture[])
{
    if(!this->blockImage->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->blockImage->loadFromFile(file_texture);
    }
    this->block->setTexture(*blockImage);
    this->block->setPosition(500,500);
}

Block::~Block()
{
    //dtor
}

sf::Sprite* Block::getBlock()
{
    return this->block;
}
