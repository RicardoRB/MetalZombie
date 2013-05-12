#include "../include/Shot.h"

Shot::Shot()
{
    //ctor
}

Shot::Shot(char file_texture[]) : Object(file_texture)
{
    //ctor father
    this->velX = 16;
}

Shot::~Shot()
{
    //dtor
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
