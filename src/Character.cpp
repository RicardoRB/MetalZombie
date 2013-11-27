#include "../include/Character.h"

Character::Character() : Object() {
    //ctor
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();
    this->life = true;
    this->movingLeft = false;
    this->movingRight = false;
    this->jumping = false;
    this->endJumping = true;
    this->attacking = false;
}

Character::Character(char file_texture[]) : Object(file_texture) {

}

Character::Character(sf::Texture* _texture) : Object(_texture) {

}

Character::~Character() {
    //dtor
    delete sprite;
    delete texture;
}

void Character::setVelX(float _velX) {
    this->speed.x = _velX;
}

float Character::getVelX() {
    return speed.x;
}

void Character::setVelY(float _velY) {
    this->speed.y = _velY;
}

float Character::getVelY() {
    return speed.y;
}

bool Character::ismovingRight() {
    return movingRight;
}

void Character::setmovingRight(bool moving) {
    this->movingRight = moving;
}

bool Character::ismovingLeft() {
    return movingLeft;
}

void Character::setmovingLeft(bool moving) {
    this->movingLeft = moving;
}

bool Character::isJumping() {
    return jumping;
}

void Character::setJumping(bool _Jumping) {
    this->jumping = _Jumping;
}

bool Character::isEndJumping() {
    return endJumping;
}

void Character::setEndJumping(bool _endJumping) {
    this->endJumping = _endJumping;
}

bool Character::isFalling() {
    return this->falling;
}

void Character::setFalling(bool _falling) {
    this->falling = _falling;
}

bool Character::isAtacking() {
    return attacking;
}

void Character::setAttacking(bool _Attacking) {
    this->attacking = _Attacking;
}

bool Character::isLookingRight() {
    return this->lookRight;
}

bool Character::isLookingLeft() {
    return this->lookLeft;
}

bool Character::isLife() {
    return this->life;
}

void Character::setLife(bool _life) {
    this->life = _life;
}
