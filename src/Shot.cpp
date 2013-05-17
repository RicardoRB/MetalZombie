#include "../include/Shot.h"
#include <iostream>

Shot::Shot()
{
    //ctor
}

Shot::Shot(char file_texture[]) : Object(file_texture)
{
    //ctor father
    this->velX = 30;
    this->shot = true;
}

Shot::~Shot()
{
    //dtor
}

void Shot::moveShot(bool _right)
{
    if(_right){
        this->getSpriteObject()->move(this->getVelX(),0);
        this->setPosWindowX((this->getPosWindowX()+this->getVelX()));
    }else{
        this->getSpriteObject()->move(-this->getVelX(),0);
        this->setPosWindowX((this->getPosWindowX()-this->getVelX()));
    }
}

void Shot::setPosWindowX(float _posWindowX)
{
    posWindowX = _posWindowX;
}

float Shot::getPosWindowX()
{
    return this->posWindowX;
}

float Shot::getVelX()
{
    return this->velX;
}

bool Shot::isShot()
{
    return this->shot;
}

void Shot::setShot(bool _shot)
{
    this->shot = _shot;
}

bool Shot::isDirectionRight(){
    return this->directionRight;
}
void Shot::setDirectionRight(bool _direction){
    this->directionRight = _direction;
}
