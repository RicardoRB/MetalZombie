#include "../include/Zombie.h"

Zombie::Zombie()
{
    //ctor
}

Zombie::Zombie(char file_texture[])
{
    if(!texture->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->texture->loadFromFile(file_texture);
    }
    //Player
    this->image_vector.top = 383;
    this->image_vector.left = 213;
    this->image_vector.width = 55;
    this->image_vector.height = 65;
    this->sprite->setTextureRect(image_vector);
    this->sprite->setTexture(*texture);
    this->sprite->setOrigin(13.5,13.f);
    //this->sprite->setPosition(500.f,100.f);
    this->sprite->setScale(-1.f,1.f);
    this->velX = 1;
    this->lookRight = false;
    this->lookLeft = true;
    this->posWindowX = this->sprite->getPosition().x;
    this->posWindowY = this->sprite->getPosition().y;
}

Zombie::~Zombie()
{
    //dtor
}

void Zombie::moveLeft()
{
    this->attacking = false;
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    this->image_vector.top = 383;
    this->image_vector.width = 55;
    this->image_vector.height = 65;
    if(this->image_vector.left >= 397) {
        this->image_vector.left = 213;
    }
    if(this->image_vector.left >= 213) {
        this->image_vector.left += image_vector.width + 11;
    } else {
        this->image_vector.left = 213;
    }
    this->sprite->setTextureRect(image_vector);
    posWindowX -= velX;
    this->sprite->move(-velX,velY);
}

void Zombie::attack()
{
    this->attacking = true;
    this->image_vector.top = 559;
    this->image_vector.width = 84;
    this->image_vector.height = 77;
    this->sprite->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y - 12);
    if(this->image_vector.left >= 490) {
        this->image_vector.left = 167;
    }
    if(this->image_vector.left >= 167) {
        this->image_vector.left += image_vector.width;
    } else {
        this->image_vector.left = 167;
    }
    this->sprite->setTextureRect(image_vector);
}
