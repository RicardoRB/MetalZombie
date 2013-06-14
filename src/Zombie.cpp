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
    }
    this->sprite->setTextureRect(image_vector);
    posWindowX -= velX;
    this->sprite->move(-velX,velY);
}

void Zombie::attack(Player *_player)
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
        if(this->image_vector.left >= 510){
            _player->die();
        }
    }
    this->sprite->setTextureRect(image_vector);
}

void Zombie::die(){
    this->life = false;
    this->sprite->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y - 600.f);
    this->image_vector.left = 0;
    this->image_vector.top = 753;
    this->image_vector.width = 152;
    this->image_vector.height = 123;
    for(int i = 0; i<3; i++){
        this->image_vector.left += image_vector.width;
        this->sprite->setTextureRect(image_vector);
    }
    this->image_vector.left = 0;
    this->image_vector.top = 913;
    this->image_vector.width = 158;
    this->image_vector.height = 149;
    for(int i = 0; i<2; i++){
        this->image_vector.left += image_vector.width;
        this->sprite->setTextureRect(image_vector);
    }
}
