#include "../include/Player.h"

Player::Player(char file_texture[])
{
    this->texture.loadFromFile(file_texture);
    this->image_vector.top = 177;
    this->image_vector.left = 20;
    this->image_vector.width = 26;
    this->image_vector.height = 27;
    this->sprite.setTextureRect(image_vector);
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(13.5,13.f);
    this->posInit();
}

Player::~Player()
{
    //dtor
}
