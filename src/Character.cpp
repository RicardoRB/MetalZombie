#include "../include/Character.h"

Character::Character()
{
    //ctor
}

Character::~Character()
{
    //dtor
}

float Character::getVelX()
{
    return velX;
}

bool Character::ismovingRight()
{
    return movingRight;
}

void Character::setmovingRight(bool moving)
{
    this->movingRight = moving;
}

bool Character::ismovingLeft()
{
    return movingLeft;
}

void Character::setmovingLeft(bool moving)
{
    this->movingLeft = moving;
}

bool Character::isJumping()
{
    return jumping;
}

bool Character::isEndJumping()
{
    return endJumping;
}

void Character::attack()
{

};

void Character::moveRight()
{
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
}

void Character::moveLeft()
{
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
    this->sprite.move(-velX,velY);
}

void Character::moveRemain()
{
    this->movingLeft = false;
    this->movingRight = false;
    this->image_vector.left = 40;
    this->image_vector.top = 350;
    this->sprite.setTextureRect(image_vector);
}

void Character::jump()
{
    //The player go the maximum position to jump
    if(this->sprite.getPosition().y <= 550.f) {
        this->jumping = true;
        endJumping = false;
        this->velY = 0;
    } else {
        this->velY = -8.f;
    }
    this->sprite.move(0,velY);
}

void Character::falling()
{
    //Collision with the floor (not yet implemented)
    if(sprite.getPosition().y >= 680.f) {
        this->velY = 0;
        endJumping = true;
    } else {
        jumping = false;
        endJumping = false;
        this->velY = 13.f;
    }
    this->sprite.move(0,velY);
}
