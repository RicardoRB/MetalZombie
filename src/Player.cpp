#include "../include/Player.h"
#include <iostream>

Player::Player(char file_texture[])
{
    if(!texture->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->texture->loadFromFile(file_texture);
    }
    //Player
    this->image_vector.top = 350;
    this->image_vector.left = 40;
    this->image_vector.width = 52;
    this->image_vector.height = 58;
    this->sprite.setTextureRect(image_vector);
    this->sprite.setTexture(*texture);
    this->sprite.setOrigin(13.5,13.f);
    this->sprite.setPosition(100.f,100.f);

    //Shot
    this->velX = 12;
    this->posWindowX = this->sprite.getPosition().x;
    this->posWindowY = this->sprite.getPosition().y;
}

Player::~Player()
{
    //dtor
}

void Player::moveRight()
{
    this->lookLeft = false;
    this->lookRight = true;
    this->movingLeft = false;
    this->movingRight = true;
    if(this->image_vector.left >= 432) {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112) {
        this->image_vector.left += 52 + 12;
    } else {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(-1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    //The background start move when the player will go
    //middle of the window
    if(this->posWindowX <= 512) {
        this->posWindowX += velX;
        this->sprite.move(velX,velY);
    } else {
        //Will move the player until the end of the picture
        //when the player arrive at the end of the picture, will move normal
        if(this->sprite.getPosition().x <= 9728) {
            this->sprite.move(velX,velY);
            camera.move(velX,0);
        } else {
            //The player will not can go out the window
            if(this->posWindowX <= 960) {
                this->posWindowX += velX;
                this->sprite.move(velX,velY);
            }
        }
    }
}

void Player::moveLeft()
{
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    if(this->image_vector.left >= 432) {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112) {
        this->image_vector.left += 52 + 12;
    } else {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    //The player will not can go out the window
    if(this->posWindowX >= 50) {
        posWindowX -= velX;
        this->sprite.move(-velX,velY);
    }
}

void Player::attack()
{
    this->attacking = true;
    this->shot->shot_vector.top = 678;
    this->shot->shot_vector.left = 1266;
    this->shot->shot_vector.width = 16;
    this->shot->shot_vector.height = 16;
    this->shot->getSpriteObject()->setTextureRect(this->shot->shot_vector);
    this->shot->getSpriteObject()->setPosition(this->sprite.getPosition().x,this->sprite.getPosition().y + 15);
    this->shot->setPosWindowX(this->shot->getSpriteObject()->getPosition().x);
}

Shot* Player::getShot()
{
    return this->shot;
}


