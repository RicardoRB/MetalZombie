#include "../include/Player.h"

Player::Player(char file_texture[]) {
    this->texture.loadFromFile(file_texture);
    this->image_vector.top = 350;
    this->image_vector.left = 40;
    this->image_vector.width = 52;
    this->image_vector.height = 58;
    this->sprite.setTextureRect(image_vector);
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(13.5,13.f);
    this->posInit();
}

Player::~Player() {
    //dtor
}
