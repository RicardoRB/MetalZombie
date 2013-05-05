#include "../include/Object.h"

Object::Object()
{
    //ctor
}

Object::Object(char file_texture[])
{
    if(!this->objectImage->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->objectImage->loadFromFile(file_texture);
    }
    this->objectImage->setRepeated(true);
    this->object->setTexture(*objectImage);
}

Object::~Object()
{
    //dtor
    delete object;
    delete objectImage;
}

sf::Sprite* Object::getSpriteObject()
{
    return this->object;
}
