#include "../include/Character.h"

Character::Character()
{
    //ctor
    this->texture = new sf::Texture();
    this->life = true;
    this->movingLeft = false;
    this->movingRight = false;
    this->jumping = false;
    this->endJumping = true;
    this->attacking = false;
    this->lookRight = false;
    this->lookLeft = true;
}

Character::~Character()
{
    //dtor
    delete texture;
}

float Character::getVelX()
{
    return velX;
}

void Character::setVelY(float _velY)
{
    this->velY = _velY;
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

void Character::setEndJumping(bool _endJumping)
{
    this->endJumping = _endJumping;
}

bool Character::isAtacking()
{
    return attacking;
}

void Character::setAttacking(bool _Attacking){
    this->attacking = _Attacking;
}

bool Character::isLookingRight(){
    return this->lookRight;
}

bool Character::isLookingLeft(){
    return this->lookLeft;
}

void Character::attack()
{

};

void Character::moveRight()
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
}

void Character::moveLeft()
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
        this->velY = -12.f;
    }
    this->sprite.move(0,velY);
}

void Character::falling()
{
    jumping = false;
    endJumping = false;
    this->velY = 1.f;
    this->sprite.move(0,velY);
}
