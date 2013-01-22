#include "../include/Player.h"


Player::Player()
{

}

Player::Player(char file_texture[])
{
    this->texture.loadFromFile(file_texture);
    this->r1.top = 177;
    this->r1.left = 20;
    this->r1.height = 27;
    this->r1.width = 26;
    this->sprite.setTextureRect(r1);
    this->sprite.setTexture(texture);
    this->posInit();
}

Player::~Player()
{
    //dtor
}
