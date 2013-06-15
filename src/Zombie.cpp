#include "../include/Zombie.h"

Zombie::Zombie() {
    //ctor
}

Zombie::Zombie(char file_texture[]) {
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
    this->sprite->setScale(-1.f,1.f);
    this->velX = 1;
    this->lookRight = false;
    this->lookLeft = true;
    this->posWindowX = this->sprite->getPosition().x;
    this->posWindowY = this->sprite->getPosition().y;
}

Zombie::~Zombie() {
    //dtor
}

void Zombie::moveLeft() {

    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    this->image_vector.top = 383;
    this->image_vector.width = 55;
    this->image_vector.height = 65;
    if(this->image_vector.left >= 397 || (!this->movingLeft && this->attacking)) {
        this->image_vector.left = 213;
    }
    if(this->image_vector.left >= 213) {
        this->image_vector.left += image_vector.width + 11;
    }
    this->sprite->setTextureRect(image_vector);
    posWindowX -= velX;
    this->sprite->move(-velX,velY);
    this->attacking = false;
}

void Zombie::attack(Player *_player) {
    this->image_vector.top = 559;
    this->image_vector.width = 84;
    this->image_vector.height = 77;
    this->sprite->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y - 15);
    if(this->image_vector.left >= 490 || (this->movingLeft && !this->attacking)) {
        this->image_vector.left = 167;
    }
    if(this->image_vector.left >= 167) {
        this->image_vector.left += image_vector.width;
        if(this->image_vector.left >= 503) {
            this->sprite->setTextureRect(image_vector);
            _player->die();
        }
    }
    this->sprite->setTextureRect(image_vector);
    this->attacking = true;
}

void Zombie::die() {
    this->image_vector.left = 0;
    this->sprite->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y - 61.f);
    this->image_vector.top = 753;
    this->image_vector.width = 152;
    this->image_vector.height = 123;
    this->sprite->setTextureRect(image_vector);
}
