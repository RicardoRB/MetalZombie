#include "../include/Object.h"

Object::Object() {
    //ctor
    objectImage = new sf::Texture();
    object = new sf::Sprite();
}

Object::Object(char file_texture[]) {
    objectImage = new sf::Texture();
    object = new sf::Sprite();
    if(!this->objectImage->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->objectImage->loadFromFile(file_texture);
    }
    //this->objectImage->setRepeated(true);
    this->object->setTexture(*objectImage);

}

Object::~Object() {
    //dtor
    delete object;
    delete objectImage;
}

sf::Sprite* Object::getSpriteObject() {
    return this->object;
}

sf::IntRect Object::getObjectVector() {
    return this->objectVector;
}

void Object::setObjectVector(sf::IntRect _rect) {
    this->objectVector = _rect;
    this->object->setTextureRect(_rect);
}
