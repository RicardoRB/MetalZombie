#include "../include/Character.h"

Character::Character()
{
    //ctor
}

Character::~Character()
{
    //dtor
}

void Character::posInit()
{
    this->sprite.setPosition(100.f,680.f);
    this->posX = 100.f;
    this->posY = 680.f;
};

void Character::attack()
{

};

void Character::moveRight()
{
    this->movingLeft = false;
    this->movingRight = true;
    this->posX += 12;
    this->velX = 12;
    if(this->image_vector.left >= 432)
    {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112)
    {
        this->image_vector.left += 52 + 12;
    }
    else
    {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(-1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    this->sprite.move(velX,velY);
}

bool Character::ismovingRight()
{
    return movingRight;
}

void Character::setmovingRight(bool moving)
{
    this->movingRight = moving;
}


void Character::moveLeft()
{
    this->movingRight = false;
    this->movingLeft = true;
    this->posX -= 12;
    this->velX = -12;
    //Will not
    if(this->image_vector.left >= 432)
    {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112)
    {
        this->image_vector.left += 52 + 12;
    }
    else
    {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    this->sprite.move(velX,velY);
}

bool Character::ismovingLeft()
{
    return movingLeft;
}

void Character::setmovingLeft(bool moving)
{
    this->movingLeft = moving;
}

void Character::moveRemain()
{
    this->movingLeft = false;
    this->movingRight = false;
    this->velX = 0;
    this->velY = 0;
    this->image_vector.left = 40;
    this->image_vector.top = 352;
    this->sprite.setTextureRect(image_vector);

}


float Character::getVelX()
{
    return velX;
}

void Character::jump()
{
    if(!this->jumping)
    {
        if(posY <= 550)
        {
            this->jumping = true;
        }
        else
        {
            this->posY -= 10;
            this->velY = -10;
            this->sprite.move(velX,velY);
        }
        std::cout << posY << std::endl;
    }
}

void Character::falling()
{
    if(posY >= 680)
    {
        //this->posY = 680;
        this->sprite.move(velX,0);
    }
    else
    {
        jumping = false;
        this->posY += 10;
        this->velY = 10;
        this->sprite.move(velX,velY);
    }
}

bool Character::isJumping()
{
    return jumping;
}

bool Character::isEndJumping()
{
    return endJumping;
}
