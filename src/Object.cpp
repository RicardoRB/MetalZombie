#include "../include/Object.h"

Object::Object() {
    //ctor
    texture = new sf::Texture();
    sprite = new sf::Sprite();
}

Object::Object(char file_texture[]) {
    texture = new sf::Texture();
    sprite = new sf::Sprite();
    this->changeTexture(file_texture);
}

Object::Object(sf::Texture* _texture) {
    texture = _texture;
    sprite = new sf::Sprite();
    this->sprite->setTexture(*texture);
}

Object::~Object() {
    //dtor
    delete sprite;
    delete texture;
}

sf::Sprite* Object::getSprite() {
    return this->sprite;
}

sf::Texture* Object::getTexture() {
    return this->texture;
}

sf::IntRect Object::getObjectVector() {
    return this->objectVector;
}

void Object::setObjectVector(sf::IntRect _rect) {
    this->objectVector = _rect;
    this->sprite->setTextureRect(_rect);
}

void Object::changeTexture(char file_texture[]) {
    if(!this->texture->loadFromFile(file_texture)) {
//        std::cout << "Error file texture player" << std::endl;
    } else {
        this->texture->loadFromFile(file_texture);
    }
    this->sprite->setTexture(*texture);
}
